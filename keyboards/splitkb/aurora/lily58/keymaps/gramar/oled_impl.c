//
// Created by gramar on 3/7/24.
//

#include "custom_constants.h"

const uint8_t OLED_DEFAULT_LAYER_START_LINE   = 2;
const uint8_t OLED_DEFAULT_LAYER_CONTENT_LINE = 4;

void oled_write_default_layer(kb_layers layer) {
    // `DV   ` padded by 3 spaces
    const char DVORAK[6] = "DV   ";
    // `DV-AN`
    const char DVORANS[6] = "DV-AN";
    // `QW-AN`
    const char QWERTY[6] = "QW-AN";
    // `QW-GM`
    const char QWERTY_GM[6] = "QW-GM";
    switch (layer) {
        case _DVORAK:
            oled_set_cursor(0, OLED_DEFAULT_LAYER_CONTENT_LINE);
            oled_write(DVORAK, false);
            oled_render_dirty(true);
            break;
        case _DVORAK_ANSI:
            oled_set_cursor(0, OLED_DEFAULT_LAYER_CONTENT_LINE);
            oled_write(DVORANS, false);
            oled_render_dirty(true);
            break;
        case _QWERTY_ANSI:
            oled_set_cursor(0, OLED_DEFAULT_LAYER_CONTENT_LINE);
            oled_write(QWERTY, false);
            oled_render_dirty(true);
            break;
        case _QWERTY_GAMING:
            oled_set_cursor(0, OLED_DEFAULT_LAYER_CONTENT_LINE);
            oled_write(QWERTY_GM, false);
            oled_render_dirty(true);
            break;
        default:
            break;
    }
}

const uint8_t OLED_MOMENTARY_LAYER_START_LINE   = 6;
const uint8_t OLED_MOMENTARY_LAYER_CONTENT_LINE = 8;

void oled_write_momentary_layer(kb_layers layer, bool pressed) {
    // `NONE `, padded 1 spaces
    const char NO_MO_LAYER[6] = "NONE ";
    // `LOWER`
    const char LOWER_OUT[6] = "LOWER";
    // `RAISE`
    const char RAISE_OUT[6] = "RAISE";
    // `NUM  `, padded 2 spaces
    const char NUM_OUT[6] = "NUM  ";
    // `SETTS`
    const char SETTINGS_OUT[6] = "SETTS";
    if (pressed) {
        switch (layer) {
            case _LOWER:
            case _LOWER_ANSI:
                oled_set_cursor(0, OLED_MOMENTARY_LAYER_CONTENT_LINE);
                oled_write(LOWER_OUT, false);
                oled_render_dirty(true);
                break;
            case _RAISE:
                oled_set_cursor(0, OLED_MOMENTARY_LAYER_CONTENT_LINE);
                oled_write(RAISE_OUT, false);
                oled_render_dirty(true);
                break;
            case _NUM:
                oled_set_cursor(0, OLED_MOMENTARY_LAYER_CONTENT_LINE);
                oled_write(NUM_OUT, false);
                oled_render_dirty(true);
                break;
            case _SETTINGS:
                oled_set_cursor(0, OLED_MOMENTARY_LAYER_CONTENT_LINE);
                oled_write(SETTINGS_OUT, false);
                oled_render_dirty(true);
                break;
            default:
                break;
        }
    } else {
        oled_set_cursor(0, OLED_MOMENTARY_LAYER_CONTENT_LINE);
        oled_write(NO_MO_LAYER, false);
        oled_render_dirty(true);
    }
}

static void inline __attribute__((always_inline)) oled_write_checked_at(bool checked, uint8_t line) {
    // `[X]  `, padded 2 spaces
    const char _CHECKED[6] = "[X]  ";
    // `[_]  `, padded 2 spaces
    const char _UNCHECKED[6] = "[_]  ";
    if (checked) {
        oled_set_cursor(0, line);
        oled_write(_CHECKED, false);
    } else {
        oled_set_cursor(0, line);
        oled_write(_UNCHECKED, false);
    }
    oled_render_dirty(true);
}

const uint8_t OLED_SHIFT_START_LINE   = 2;
const uint8_t OLED_SHIFT_CONTENT_LINE = 4;

void oled_write_shift_update(bool pressed) {

    oled_write_checked_at(pressed, OLED_SHIFT_CONTENT_LINE);
    oled_render_dirty(true);
}

const uint8_t OLED_CTRL_START_LINE   = 6;
const uint8_t OLED_CTRL_CONTENT_LINE = 8;

void oled_write_ctrl_update(bool pressed) {
    oled_write_checked_at(pressed, OLED_CTRL_CONTENT_LINE);
    oled_render_dirty(true);
}

static void oled_write_separator_line_after(uint8_t line) {
    // 8 pixels line height, plus half a line
    uint8_t y = line * 8 + 3;
    if (y >= 128) {
        return;
    }
    // 32 pixels per line
    for (uint8_t x = 0; x < 32; ++x) {
        oled_write_pixel(x, y, true);
    }
}

void oled_write_initial_state(void) {
    // Also resets cursor
    oled_clear();
    if (is_keyboard_left()) {
        oled_write("LEFT ", false);
        oled_write_separator_line_after(1);
        oled_set_cursor(0, OLED_DEFAULT_LAYER_START_LINE);
        oled_write("MAP   ", false);
        oled_write_default_layer(_DVORAK);
        oled_write_separator_line_after(OLED_DEFAULT_LAYER_CONTENT_LINE + 1);
        oled_set_cursor(0, OLED_MOMENTARY_LAYER_START_LINE);
        oled_write("LAYER ", false);
        oled_write_momentary_layer(_LOWER, false);
        oled_write_separator_line_after(OLED_MOMENTARY_LAYER_CONTENT_LINE + 1);
    } else {
        oled_write("RIGHT", false);
        oled_write_separator_line_after(1);
        oled_set_cursor(0, OLED_SHIFT_START_LINE);
        oled_write("SHIFT", false);
        oled_write_shift_update(false);
        oled_write_separator_line_after(OLED_SHIFT_CONTENT_LINE + 1);
        oled_set_cursor(0, OLED_CTRL_START_LINE);
        oled_write("CTRL ", false);
        oled_write_ctrl_update(false);
        oled_write_separator_line_after(OLED_CTRL_CONTENT_LINE + 1);
    }
    oled_render_dirty(true);
}