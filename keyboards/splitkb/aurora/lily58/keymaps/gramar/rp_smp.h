//
// Created by gramar on 3/14/24.
//

#ifndef QMK_FIRMWARE_RP_SMP_H
#define QMK_FIRMWARE_RP_SMP_H
typedef union {
    struct init_oled_state {
    } init;
    struct default_layer {
        uint8_t layer;
    } df_layer;
    struct momentary_layer {
        uint8_t layer;
    } mo_layer;
    struct shift_kind {
        uint8_t pressed;
    } shift;
    struct ctrl_kind {
        uint8_t pressed;
    } ctrl;
} render_msg_kind;

typedef struct {
    uint8_t kind;
    render_msg_kind msg;
} render_msg;

void push_message_to_queue(render_msg msg);

render_msg await_next_message_on_queue(void);

#endif // QMK_FIRMWARE_RP_SMP_H
