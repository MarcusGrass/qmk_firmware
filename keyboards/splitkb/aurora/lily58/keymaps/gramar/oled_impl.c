//
// Created by gramar on 3/7/24.
//

#include "custom_constants.h"
#include "ch.h"

#define ASCII_SPACE 32

// Wakeup for the writer thread
static SEMAPHORE_DECL(oled_writer_semaphore, 0);

// Mutex for data manipulation
static MUTEX_DECL(oled_data_mutex);

#define oled_worker_wakeup() chSemReset(&oled_writer_semaphore, 0)

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
            var_name.header_needs_commit = false;                                          \
            needs_render                 = true;                                           \
        }                                                                                  \
        if (var_name.content_needs_commit) {                                               \
            oled_set_cursor(0, line_no + 1);                                               \
            oled_write(var_name.content, false);                                           \
            var_name.header_needs_commit = false;                                          \
            needs_render                 = true;                                           \
        }                                                                                  \
        return needs_render;\
    }

// One line is 5 chars, start line is where the header starts
OLED_BUF_STRUCT(left_layer_oled_buffer, left_layer_buf, left_layer_buffer_commit, 2, "MAP", 6)
OLED_BUF_STRUCT(left_momentary_layer_oled_buffer, left_momentary_layer_buf, left_momentary_layer_buffer_commit, 5, "LAY", 6)
OLED_BUF_STRUCT(left_shift_oled_buffer, left_shift_buf, left_shift_buffer_commit, 11, "SHIFT", 6)
OLED_BUF_STRUCT(left_ctrl_oled_buff, left_ctrl_buf, left_ctrl_buffer_commit, 14, "CTRL", 6)

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
        chMtxLock(&oled_data_mutex);
        left_layer_buf.header_needs_commit = oled_write_layer_update_into_buffer(layer, left_layer_buf.content);
        chMtxUnlock(&oled_data_mutex);
        oled_worker_wakeup();
    }
}
static bool inline __attribute__((always_inline)) oled_write_momentary_layer_update_into_buffer(kb_layers layer, bool pressed, char buf[6]) {
    // `[___]`, padded 2 spaces
    const char NO_MO_LAYER[5] = {91, 95, 95, 95, 93};
    // `LOWER`
    const char LOWER_OUT[5] = {91, 76, 79, 87, 93};
    // `RAISE`
    const char RAISE_OUT[5] = {91, 82, 65, 73, 93};
    // `NUM  `
    const char NUM_OUT[5] = {91, 78, 85, 77, 93};
    // `SETTS`
    const char SETTINGS_OUT[5] = {91, 83, 69, 84, 93};
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
        chMtxLock(&oled_data_mutex);
        left_momentary_layer_buf.content_needs_commit = oled_write_momentary_layer_update_into_buffer(layer, pressed, left_momentary_layer_buf.content);
        chMtxUnlock(&oled_data_mutex);
        oled_worker_wakeup();
    }
}

static void inline __attribute__((always_inline)) oled_write_checked_modifier_into_buffer(bool checked, char buf[6]) {
    // `[X]  `, padded 2 spaces
    const char CHECKED[5] = {91, 88, 93, ASCII_SPACE, ASCII_SPACE};
    // `[_]  `, padded 2 spaces
    const char UNCHECKED[5] = {91, 95, 93, ASCII_SPACE, ASCII_SPACE};
    if (checked) {
        memcpy(buf, CHECKED, 5);
    } else {
        memcpy(buf, UNCHECKED, 5);
    }
}

void oled_display_update_shift(bool pressed) {
    if (is_keyboard_left()) {
        chMtxLock(&oled_data_mutex);
        oled_write_checked_modifier_into_buffer(pressed, left_shift_buf.content);
        left_shift_buf.content_needs_commit = true;
        chMtxUnlock(&oled_data_mutex);
        oled_worker_wakeup();
    }
}

void oled_display_update_ctrl(bool pressed) {
    if (is_keyboard_left()) {
        chMtxLock(&oled_data_mutex);
        oled_write_checked_modifier_into_buffer(pressed, left_ctrl_buf.content);
        left_ctrl_buf.content_needs_commit = true;
        chMtxUnlock(&oled_data_mutex);
        oled_worker_wakeup();
    }
}

bool oled_display_commit(void) {
    static bool left_oled_needs_header  = true;
    static bool right_oled_needs_header = true;
    bool        needs_render            = false;
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    if (is_keyboard_left()) {
        if (left_oled_needs_header) {
            oled_clear();
            oled_write("LEFT ", false);
            left_oled_needs_header = false;
            needs_render           = true;
        }
        if (left_layer_buffer_commit()) {
            needs_render = true;
        }
        if (left_momentary_layer_buffer_commit()) {
            needs_render = true;
        }
        if (left_shift_buffer_commit()) {
            needs_render = true;
        }
        if (left_ctrl_buffer_commit()) {
            needs_render = true;
        }
    } else {
        if (right_oled_needs_header) {
            oled_clear();
            oled_write("RIGHT", false);
            right_oled_needs_header = false;
            needs_render            = true;
        }
    }
    return needs_render;
}


static THD_WORKING_AREA(oled_writer_working_area, 1048);


static THD_FUNCTION(oled_writer_worker, arg) {
    chMtxLock(&oled_data_mutex);
    oled_clear();
    oled_display_commit();
    oled_render_dirty(true);
    chMtxUnlock(&oled_data_mutex);
    for (;;) {
        chSemWait(&oled_writer_semaphore);
        chMtxLock(&oled_data_mutex);
        if (oled_display_commit()) {
            oled_render_dirty(false);
        }
        chMtxUnlock(&oled_data_mutex);
    }
}

// Worker thread handle

void oled_worker_start(void) {
    static thread_t *worker_thread_handle = 0;
    if (!worker_thread_handle) {
        worker_thread_handle = chThdCreateStatic(oled_writer_working_area, sizeof(oled_writer_working_area), LOWPRIO, oled_writer_worker, NULL);
    }
}