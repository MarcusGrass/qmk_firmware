//
// Created by gramar on 3/14/24.
//
#include "rp_smp.h"
#include "secondary_client.h"
void worker_submit_init_message(void) {
    render_msg msg = {.kind = 1, .msg = {.init = {}}};
    push_message_to_queue(msg);
}
void worker_submit_default_layer_change(kb_layers layer) {
    render_msg msg = {.kind = 2, .msg = {.df_layer = {layer}}};
    push_message_to_queue(msg);
}
void worker_submit_momentary_layer_change(kb_layers layer, bool pressed) {
    render_msg msg = {.kind = 3, .msg = {.mo_layer = {layer, pressed}}};
    push_message_to_queue(msg);
}
void worker_submit_shift(bool pressed) {
    uint8_t    pressed_num = (uint8_t)pressed;
    render_msg msg         = {.kind = 4, .msg = {.shift = {pressed_num}}};
    push_message_to_queue(msg);
}
void worker_submit_ctrl(bool pressed) {
    uint8_t    pressed_num = (uint8_t)pressed;
    render_msg msg         = {.kind = 5, .msg = {.ctrl = {pressed_num}}};
    push_message_to_queue(msg);
}