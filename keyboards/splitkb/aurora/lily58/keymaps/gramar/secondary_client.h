//
// Created by gramar on 3/14/24.
//

#ifndef QMK_FIRMWARE_SECONDARY_CLIENT_H
#define QMK_FIRMWARE_SECONDARY_CLIENT_H
#include "custom_constants.h"

void submit_init_message(void);
void submit_default_layer_change(kb_layers layer);
void submit_momentary_layer_change(kb_layers layer);
void submit_shift(bool pressed);
void submit_ctrl(bool pressed);


#endif // QMK_FIRMWARE_SECONDARY_CLIENT_H
