//
// Created by gramar on 3/14/24.
//

#include <string.h>
#include "ch.h"
#include "rp_smp.h"

#define _RENDER_MSG_CAP 16
// Mutex for data manipulation
static MUTEX_DECL(oled_data_mutex);

static CONDVAR_DECL(oled_data_condvar);

typedef struct {
    render_msg messages[_RENDER_MSG_CAP];
    uint8_t offset;
    uint8_t count;
} render_message_queue;

static render_message_queue RENDER_MESSAGE_QUEUE = {{{0}}, 0, 0};

// Core 0 pushes message to the render queue
void push_message_to_queue(render_msg msg) {
    // Lock mutex
    chMtxLock(&oled_data_mutex);
    if (RENDER_MESSAGE_QUEUE.count >= _RENDER_MSG_CAP) {
        // Not much to do, early exit if full
        return;
    }
    // The next open slot is the start offset + count, since
    uint8_t next_offset = RENDER_MESSAGE_QUEUE.offset + RENDER_MESSAGE_QUEUE.count;
    // Wrap around if necessary
    if (next_offset >= _RENDER_MSG_CAP) {
        next_offset -= _RENDER_MSG_CAP;
    }
    // Insert at next open slot
    RENDER_MESSAGE_QUEUE.messages[next_offset] = msg;
    // Increment count to move the next open slot
    RENDER_MESSAGE_QUEUE.count += 1;
    chCondSignal(&oled_data_condvar);
    // Release lock
    chMtxUnlock(&oled_data_mutex);
}

// Core 1 pops messages off the queue
render_msg await_next_message_on_queue(void) {
    // Lock mutex
    chMtxLock(&oled_data_mutex);
    // While count is 0, wait for condvar to get notified
    while (RENDER_MESSAGE_QUEUE.count == 0) {
        chCondWait(&oled_data_condvar);
    }
    render_msg msg;
    // Copy the message at the current offset into the receiver
    memcpy(&msg, &RENDER_MESSAGE_QUEUE.messages[RENDER_MESSAGE_QUEUE.offset], sizeof(render_msg));
    // Increment the offset
    uint8_t next_offset = RENDER_MESSAGE_QUEUE.offset + 1;
    // Wrap if necessary
    if (next_offset >= _RENDER_MSG_CAP) {
        next_offset = 0;
    }
    // Set offset
    RENDER_MESSAGE_QUEUE.offset = next_offset;
    // Decrement count, definitely larger than 0 before this
    RENDER_MESSAGE_QUEUE.count -= 1;
    // Unlock no wakeup, this is Core 1
    chMtxUnlock(&oled_data_mutex);
    return msg;
}