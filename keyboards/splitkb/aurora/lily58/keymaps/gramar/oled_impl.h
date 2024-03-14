//
// Created by gramar on 3/7/24.
//
#include "custom_constants.h"
#ifndef QMK_FIRMWARE_OLED_IMPL_H
#define QMK_FIRMWARE_OLED_IMPL_H
void oled_display_update_pressed_key(uint16_t keycode);
void oled_display_update_layer(kb_layers layer);
void oled_display_update_momentary_layer(kb_layers layer, bool pressed);
void oled_display_update_shift(bool pressed);
void oled_display_update_ctrl(bool pressed);
void oled_worker_start(void);
void oled_handle_sync(uint8_t in_buflen, const void* in_data);
void oled_worker_run(void);
// new
void oled_write_default_layer(kb_layers layer);
#endif // QMK_FIRMWARE_OLED_IMPL_H
