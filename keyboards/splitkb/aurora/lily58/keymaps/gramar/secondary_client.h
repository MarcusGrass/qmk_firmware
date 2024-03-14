//
// Created by gramar on 3/14/24.
//

#ifndef QMK_FIRMWARE_SECONDARY_CLIENT_H
#define QMK_FIRMWARE_SECONDARY_CLIENT_H
#include "custom_constants.h"

void worker_submit_init_message(void);
void worker_submit_default_layer_change(kb_layers layer);
void worker_submit_momentary_layer_change(kb_layers layer, bool pressed);
void worker_submit_shift(bool pressed);
void worker_submit_ctrl(bool pressed);


#endif // QMK_FIRMWARE_SECONDARY_CLIENT_H
