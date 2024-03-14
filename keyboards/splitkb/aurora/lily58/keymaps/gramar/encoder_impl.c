//
// Created by gramar on 3/7/24.
//

#include QMK_KEYBOARD_H
#include "custom_constants.h"
#include "encoder_impl.h"
#include "kb_util.h"
#include "secondary_client.h"

const kb_layers PROGMEM CYCLE_LAYERS[] = {_DVORAK, _DVORAK_ANSI, _QWERTY_ANSI, _QWERTY_GAMING};

void encoder_update(uint8_t index, bool clockwise) {
    static uint8_t encoder_layer_index = 0;
    // Only using encoder on right half, index 1 (left is 0)
    if (index == 1) {
        if (clockwise) {
            if (encoder_layer_index >= 3) {
                encoder_layer_index = 0;
            } else {
                encoder_layer_index++;
            }
        } else {
            if (encoder_layer_index < 1) {
                encoder_layer_index = 3;
            } else {
                encoder_layer_index--;
            }
        }
        update_default_layer(CYCLE_LAYERS[encoder_layer_index]);
        worker_submit_default_layer_change(CYCLE_LAYERS[encoder_layer_index]);
    }
}