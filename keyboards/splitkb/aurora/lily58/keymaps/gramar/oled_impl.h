//
// Created by gramar on 3/7/24.
//
#include "custom_constants.h"
#ifndef QMK_FIRMWARE_OLED_IMPL_H
#    define QMK_FIRMWARE_OLED_IMPL_H
// new
void oled_write_default_layer(kb_layers layer);
void oled_write_momentary_layer(kb_layers layer, bool pressed);
void oled_write_shift_update(bool pressed);
void oled_write_ctrl_update(bool pressed);
void oled_write_initial_state(void);
#endif // QMK_FIRMWARE_OLED_IMPL_H
