//
// Created by gramar on 3/7/24.
//

#include "ch.h"
#include "transactions.h"
#include "custom_constants.h"

#define ASCII_SPACE 32

// Wakeup for the writer thread
static SEMAPHORE_DECL(oled_writer_semaphore, 0);

// Mutex for data manipulation
static MUTEX_DECL(oled_data_mutex);

static CONDVAR_DECL(oled_data_condvar);

#define oled_worker_wakeup() chSemReset(&oled_writer_semaphore, 0)
#define oled_worker_sleep_short() chSemWaitTimeout(&oled_writer_semaphore, 1000)
#define oled_worker_go_to_sleep() chSemWaitTimeout(&oled_writer_semaphore, 1000)
#define oled_shared_data_lock() chMtxLock(&oled_data_mutex)
#define oled_shared_data_try_lock() chMtxTryLock(&oled_data_mutex)
#define oled_shared_data_unlock() chMtxUnlock(&oled_data_mutex)
// Wake up the worker before releasing the lock
#define oled_shared_data_release() oled_worker_wakeup(); chMtxUnlock(&oled_data_mutex)

static void oled_write_separator_line_after(uint8_t line) {
    // 8 pixels line height, plus half a line
    uint8_t y = line * 8 + 3;
    if (y >= 128) {
        return;
    }
    // 32 pixels per line
    for (uint8_t x = 0; x < 32; ++x) {
        oled_write_pixel(x, y, true);
    }
}


typedef struct {
    uint8_t kind;
    uint8_t pressed;
} oled_sync_msg;



// Define a buffer struct that defines a local buffer to which it can write its content, and a function which commits that to
// the correct place on the oled.
// On data that's updated faster than `OLED_UPDATE_INTERVAL` it prevents unnecessary calls to write to the
// oled buffer
#define OLED_BUF_STRUCT(struct_name, var_name, oled_commit_fn, line_no, hdr, content_size) \
    typedef struct {                                                                       \
        bool header_needs_commit;                                                          \
        bool content_needs_commit;                                                         \
        char header[6];                                                                    \
        char content[content_size];                                                        \
    } struct_name;                                                                         \
    static struct_name var_name = {true, true, hdr, {0}};                                  \
    static bool inline __attribute__((always_inline)) oled_commit_fn(void) {               \
        bool needs_render = false;                                                         \
        if (var_name.header_needs_commit) {                                                \
            oled_set_cursor(0, line_no);                                                   \
            oled_write(var_name.header, false);                                            \
            oled_write_separator_line_after(line_no + 3);\
            var_name.header_needs_commit = false;                                          \
            needs_render                 = true;                                           \
        }                                                                                  \
        if (var_name.content_needs_commit) {                                               \
            oled_set_cursor(0, line_no + 2);                                               \
            oled_write(var_name.content, false);                                           \
            var_name.header_needs_commit = false;                                          \
            needs_render                 = true;                                           \
        }                                                                                  \
        return needs_render;                                                               \
    }

// One line is 5 chars, start line is where the header starts
OLED_BUF_STRUCT(left_layer_oled_buffer, left_layer_buf, left_layer_buffer_commit, 2, "MAP", 6)
OLED_BUF_STRUCT(left_momentary_layer_oled_buffer, left_momentary_layer_buf, left_momentary_layer_buffer_commit, 6, "LAY", 6)

OLED_BUF_STRUCT(right_shift_oled_buffer, right_shift_buf, right_shift_buffer_commit, 2, "SHIFT", 6)
OLED_BUF_STRUCT(right_ctrl_oled_buffer, right_ctrl_buf, right_ctrl_buffer_commit, 6, "CTRL", 6)


static bool inline __attribute__((always_inline)) oled_write_layer_update_into_buffer(kb_layers layer, char buf[6]) {
    // I'm not dealing with null terminators anymore
    // `DV   ` padded by 3 spaces
    const char DVORAK[5] = {68, 86, ASCII_SPACE, ASCII_SPACE, ASCII_SPACE};
    // `DV-AN`
    const char DVORANS[5] = {68, 86, 45, 65, 78};
    // `QW-AN`
    const char QWERTY[5] = {81, 87, 45, 65, 78};
    // `QW-GM`
    const char QWERTY_GM[5] = {81, 87, 45, 71, 77};
    switch (layer) {
        case _DVORAK:
            memcpy(buf, DVORAK, 5);
            break;
        case _DVORAK_ANSI:
            memcpy(buf, DVORANS, 5);
            break;
        case _QWERTY_ANSI:
            memcpy(buf, QWERTY, 5);
            break;
        case _QWERTY_GAMING:
            memcpy(buf, QWERTY_GM, 5);
            break;
        default:
            return false;
    }
    return true;
}

void oled_display_update_layer(kb_layers layer) {
    if (is_keyboard_left()) {
        // Only on the left side, write into the in-mem buffer, then signal core 2 to wake up and write to the oled buffer
        oled_shared_data_lock();
        left_layer_buf.header_needs_commit = oled_write_layer_update_into_buffer(layer, left_layer_buf.content);
        oled_shared_data_release();
    }
}

// Write layer data into the provided buffer
static bool inline __attribute__((always_inline)) oled_write_momentary_layer_update_into_buffer(kb_layers layer, bool pressed, char buf[6]) {
    // `NONE `, padded 1 spaces
    const char NO_MO_LAYER[5] = {78, 79, 78, 69, ASCII_SPACE};
    // `LOWER`
    const char LOWER_OUT[5] = {76, 79, 87, 69, 82};
    // `RAISE`
    const char RAISE_OUT[5] = {82, 65, 73, 83, 69};
    // `NUM  `, padded 2 spaces
    const char NUM_OUT[5] = {78, 85, 77, ASCII_SPACE, ASCII_SPACE};
    // `SETTS`
    const char SETTINGS_OUT[5] = {83, 69, 84, 84, 83};
    if (pressed) {
        switch (layer) {
            case _LOWER:
            case _LOWER_ANSI:
                memcpy(buf, LOWER_OUT, 5);
                break;
            case _RAISE:
                memcpy(buf, RAISE_OUT, 5);
                break;
            case _NUM:
                memcpy(buf, NUM_OUT, 5);
                break;
            case _SETTINGS:
                memcpy(buf, SETTINGS_OUT, 5);
                break;
            default:
                return false;
        }
    } else {
        memcpy(buf, NO_MO_LAYER, 5);
    }
    return true;
}

void oled_display_update_momentary_layer(kb_layers layer, bool pressed) {
    if (is_keyboard_left()) {
        // Only displayed on left, just lock the in-mem buffer, write the new data into it, then signal core 2 to wake up and write it to the oled buffer
        oled_shared_data_lock();
        left_momentary_layer_buf.content_needs_commit = oled_write_momentary_layer_update_into_buffer(layer, pressed, left_momentary_layer_buf.content);
        oled_shared_data_release();
    }
}

static void inline __attribute__((always_inline)) oled_write_checked_modifier_into_buffer(bool checked, char buf[6]) {
    // `[X]  `, padded 2 spaces
    const char _CHECKED[5] = {91, 88, 93, ASCII_SPACE, ASCII_SPACE};
    // `[_]  `, padded 2 spaces
    const char _UNCHECKED[5] = {91, 95, 93, ASCII_SPACE, ASCII_SPACE};
    if (checked) {
        memcpy(buf, _CHECKED, 5);
    } else {
        memcpy(buf, _UNCHECKED, 5);
    }
}


// NEEDS MUTEX LOCK ON RW
static oled_sync_msg needs_send_shift = { 0, 0};

// Update shift checkbox
void oled_display_update_shift(bool pressed) {
    if (is_keyboard_left()) {
        // On left keyboard, signal to core 2 that a transaction should go out
        oled_shared_data_lock();
        needs_send_shift.kind = 1;
        needs_send_shift.pressed = (uint8_t)pressed;
        oled_shared_data_release();
    } else {
        // On right keyboard, write to in-mem buffer, signal oled-thread to write into the oled buffer by waking it up after changing state
        oled_shared_data_lock();
        oled_write_checked_modifier_into_buffer(pressed, right_shift_buf.content);
        right_shift_buf.content_needs_commit = true;
        oled_shared_data_release();
    }
}

// NEEDS MUTEX LOCK ON RW
static oled_sync_msg needs_send_ctrl = { 0, 0};

// Update shift checkbox
void oled_display_update_ctrl(bool pressed) {
    if (is_keyboard_left()) {
        // On left keyboard, signal to core 2 that a transaction should go out
        oled_shared_data_lock();
        needs_send_ctrl.kind = 2;
        needs_send_ctrl.pressed = (uint8_t)pressed;
        oled_shared_data_release();
    } else {
        // On right keyboard, write to in-mem buffer, signal oled-thread to write into the oled buffer by waking it up after changing state
        oled_shared_data_lock();
        oled_write_checked_modifier_into_buffer(pressed, right_ctrl_buf.content);
        right_ctrl_buf.content_needs_commit = true;
        oled_shared_data_release();
    }
}

// On the right side, synced data comes through function, called by core 0
void oled_handle_sync(uint8_t in_buflen, const void* in_data) {
    uint8_t len = in_buflen / sizeof(oled_sync_msg);
    if (!len) {
        return;
    }
    // Don't know if this can actually have a len != 1, but whatever
    const oled_sync_msg *msg = (const oled_sync_msg*) in_data;
    for (uint8_t i = 0; i < len; ++i) {
        const oled_sync_msg use_msg = msg[i];
        switch (use_msg.kind) {
            case 1:
                oled_display_update_shift(use_msg.pressed);
                break;
            case 2:
                oled_display_update_ctrl(use_msg.pressed);
                break;
        }
    }

}

// NEEDS LOCK SHARED MEMORY
// Commits the buffer data into oled memory
bool oled_display_commit(void) {
    // Only commit these once to the oled state
    static bool left_oled_needs_header  = true;
    static bool right_oled_needs_header = true;
    bool        needs_render            = false;
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    if (is_keyboard_left()) {
        if (left_oled_needs_header) {
            oled_clear();
            oled_write("LEFT ", false);
            oled_write_separator_line_after(1);
            left_oled_needs_header = false;
            needs_render           = true;
        }
        if (left_layer_buffer_commit()) {
            needs_render = true;
        }
        if (left_momentary_layer_buffer_commit()) {
            needs_render = true;
        }

    } else {
        if (right_oled_needs_header) {
            oled_clear();
            oled_write("RIGHT", false);
            oled_write_separator_line_after(1);
            right_oled_needs_header = false;
            needs_render            = true;
        }
        if (right_shift_buffer_commit()) {
            needs_render = true;
        }
        if (right_ctrl_buffer_commit()) {
            needs_render = true;
        }
    }
    return needs_render;
}

// Keep some vars exclusive to the worker thread
static oled_sync_msg needs_send_shift_cpy = {0, 0};
static oled_sync_msg needs_send_ctrl_cpy = {0, 0};

static void inline __attribute__((always_inline)) oled_send_transactions(void) {
    if (needs_send_shift_cpy.kind) {
        transaction_rpc_send(OLED_DATA_SYNC, sizeof(needs_send_shift_cpy), &needs_send_shift_cpy);
        needs_send_shift_cpy.kind = 0;
    }
    if (needs_send_ctrl_cpy.kind) {
        transaction_rpc_send(OLED_DATA_SYNC, sizeof(needs_send_ctrl_cpy), &needs_send_ctrl_cpy);
        needs_send_ctrl_cpy.kind = 0;
    }
}

static bool has_triggered_start = false;

void oled_run(void) {
}

// Oled worker fn, should run from core 1
void oled_worker_run(void) {
    // Busy wait for init, making sure all relevant vars are set
    while (1) {
        oled_shared_data_lock();
        if (has_triggered_start) {
            oled_shared_data_unlock();
            break;
        }
        oled_shared_data_unlock();

    }
    // Doesn't change, might as well put it in a var
    bool is_left = is_keyboard_left();
    // Lock data for initial commit
    oled_shared_data_lock();
    oled_clear();
    oled_display_commit();
    // Always render all, latency doesn't really matter on this thread
    oled_render_dirty(true);
    // Unlock post initial commit
    oled_shared_data_unlock();
    // Main render loop
    while(1) {
        // Await wakeup notification
        chSemWait(&oled_writer_semaphore);
        // Lock data modification
        oled_shared_data_lock();
        // Commit data to oled buffer, render if necessary
        if (oled_display_commit()) {
            oled_render_dirty(true);
        }
        // Copy over shared data to this thread so that we can drop the lock before running the transaction
        if (is_left) {
            needs_send_shift_cpy.kind = needs_send_shift.kind;
            needs_send_shift_cpy.pressed = needs_send_shift.pressed;

            needs_send_ctrl_cpy.kind = needs_send_ctrl.kind;
            needs_send_ctrl_cpy.pressed = needs_send_ctrl.pressed;
            needs_send_shift.kind = 0;
            needs_send_ctrl.kind = 0;
        }
        // Drop lock
        oled_shared_data_unlock();
        // Only send transactions from the left side
        if (is_left) {
            oled_send_transactions();
        }
    }
}

void oled_worker_start(void) {
    // Busy wait until we've set it
    oled_shared_data_lock();
    has_triggered_start = true;
    oled_shared_data_unlock();
}