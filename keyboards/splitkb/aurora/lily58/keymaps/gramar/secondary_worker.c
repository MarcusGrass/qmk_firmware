//
// Created by gramar on 3/14/24.
//

#include "rp_smp.h"
#include "secondary_worker.h"
#include "split_transaction.h"
#include "oled_impl.h"

void worker_run(void) {
    bool is_left = is_keyboard_left();
    while(1) {
        render_msg next_msg = await_next_message_on_queue();
        switch (next_msg.kind) {
            case 1:
                oled_write_initial_state();
                break;
            case 2:
                kb_layers df_layer = (kb_layers)next_msg.msg.df_layer.layer;
                oled_write_default_layer(df_layer);
                break;
            case 3:
                kb_layers mo_layer = (kb_layers)next_msg.msg.mo_layer.layer;
                bool pressed = next_msg.msg.mo_layer.pressed;
                oled_write_momentary_layer(mo_layer, pressed);
                break;
            case 4:
                bool pressed_shift = next_msg.msg.shift.pressed;
                if (is_left) {
                    left_side_submit_shift_transaction(pressed_shift);
                } else {
                    oled_write_shift_update(pressed_shift);
                }
                break;
            case 5:
                bool pressed_ctrl = next_msg.msg.ctrl.pressed;
                if (is_left) {
                    left_side_submit_ctrl_transaction(pressed_ctrl);
                } else {
                    oled_write_ctrl_update(pressed_ctrl);
                }
                break;
            default:
                break;
        }
    }
}
