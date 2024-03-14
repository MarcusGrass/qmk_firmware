//
// Created by gramar on 3/14/24.
//

#ifndef QMK_FIRMWARE_KD_UTIL_H
#define QMK_FIRMWARE_KD_UTIL_H
#include "custom_constants.h"

layer_state_t state_from_layer(kb_layers layer);

void update_default_layer(kb_layers layer);

#endif // QMK_FIRMWARE_KD_UTIL_H
