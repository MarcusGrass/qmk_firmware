//
// Created by gramar on 3/14/24.
//

#include QMK_KEYBOARD_H
#include "custom_constants.h"
#include "kb_util.h"
// Some code ripped from internals to make a proper layer state from a layer, if internals are changed, this is going to be spicy
layer_state_t state_from_layer(kb_layers layer) {
    action_t      action = {.code = ACTION_DEFAULT_LAYER_SET(layer)};
    uint8_t       shift  = action.layer_bitop.part * 4;
    layer_state_t bits   = ((layer_state_t)action.layer_bitop.bits) << shift;
    layer_state_t mask   = (action.layer_bitop.xbit) ? ~(((layer_state_t)0xf) << shift) : 0;
    return bits | mask;
}

// If internals are changed and this becomes a bug, just change back to `set_single_persistent_default_layer(layer)`
// not using it since it will eventually wear out the eeprom and I'd like the default layer to be the same at every start
void update_default_layer(kb_layers layer) {
    layer_state_t layer_state = state_from_layer(layer);
    default_layer_set(layer_state);
}