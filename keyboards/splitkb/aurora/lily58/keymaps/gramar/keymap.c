#include QMK_KEYBOARD_H
#include "custom_constants.h"
#include "encoder_impl.h"
#include "oled_impl.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT( \
        KC_TAB  , SH_APST, CM_LBR , DT_RBR , KC_P   , KC_Y   ,                                    KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_BSPC, \
        ESC_CTL , KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,                                    KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_ENT , \
        KC_LSFT , SCRC   , KC_Q   , KC_J   , KC_K   , KC_X   ,                                    KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_LSFT, \
        KC_LCTL , KC_LGUI, KC_LALT, KC_TRNS, LOWER  , KC_SPC , KC_LALT,                  KC_ALGR, KC_SPC , NUM    , RAISE  , KC_ALGR, SETTS  , KC_RCTL, \
                                    KC_TRNS, NO_UDSC, NO_UDSC, KC_LSFT,                  KC_TRNS, KC_TRNS, KC_BSPC, KC_TRNS                             \
        ),

    [_DVORAK_ANSI] = LAYOUT( \
        KC_TAB  , KC_QUOT, KC_COMM, KC_DOT , KC_P   , KC_Y   ,                                    KC_F   , KC_G   , KC_C   , KC_R   , KC_L   , KC_BSPC, \
        ESC_CTL , KC_A   , KC_O   , KC_E   , KC_U   , KC_I   ,                                    KC_D   , KC_H   , KC_T   , KC_N   , KC_S   , KC_ENT , \
        KC_LSFT , KC_SCLN, KC_Q   , KC_J   , KC_K   , KC_X   ,                                    KC_B   , KC_M   , KC_W   , KC_V   , KC_Z   , KC_LSFT, \
        KC_LCTL , KC_LGUI, KC_LALT, KC_TRNS, LOWANS , KC_SPC , KC_LALT,                  KC_ALGR, KC_SPC , NUM    , RAISE  , KC_ALGR, SETTS  , KC_RCTL, \
                                    KC_TRNS, AN_UDSC, AN_UDSC, KC_LSFT,                  KC_TRNS, KC_LSFT, KC_BSPC, KC_TRNS                             \
        ),

    [_QWERTY_ANSI] = LAYOUT( \
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                    KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
        ESC_CTL , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                    KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT , \
        KC_LSFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                    KC_N   , KC_M   , KC_COMM, KC_DOT , KC_QUOT, KC_LSFT, \
        KC_LCTL , KC_LGUI, KC_LALT, KC_TRNS, LOWANS , KC_SPC , KC_LALT,                  KC_ALGR, KC_SPC , NUM    , RAISE  , KC_ALGR, SETTS  , KC_RCTL, \
                                    KC_TRNS, AN_UDSC, AN_UDSC, KC_LSFT,                  KC_TRNS, KC_LSFT, KC_BSPC, KC_TRNS                             \
        ),

    [_QWERTY_GAMING] = LAYOUT( \
        KC_TAB  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                    KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC, \
        ESC_CTL , KC_T   , KC_Q   , KC_W   , KC_E   , KC_R   ,                                    KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_ENT , \
        KC_LSFT , KC_Y   , KC_A   , KC_S   , KC_D   , KC_F   ,                                    KC_N   , KC_M   , KC_COMM, KC_DOT , KC_QUOT, KC_LSFT, \
        KC_LCTL , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_M   ,                  KC_O   , KC_G   , KC_I   , RAISE  , KC_ALGR, SETTS  , KC_RCTL, \
                                    KC_LGUI, KC_LALT, KC_SPC , KC_TRNS,                  KC_TRNS, KC_U   , KC_P   , LOWER                               \
        ),

    [_LOWER] = LAYOUT( \
        KC_TRNS , KC_EXLM, NO_AT  , KC_HASH, NO_DLR , KC_PERC,                                    NO_CIRC, NO_AMPR, NO_LPRN, NO_RPRN, NO_ASTR, KC_TRNS, \
        KC_TRNS , NO_PLUS, NO_EQL , NO_LBRC, NO_RBRC, NO_QUES,                                    NO_BSLS, NO_SLSH, NO_LCBR, NO_RCBR, NO_MINS, KC_TRNS, \
        KC_TRNS , KC_TRNS, _CUT   , _COPY  , _PASTE , NO_TILD,                                    NO_GRV , NO_PIPE, NO_AA  , NO_OSLH, NO_AE  , KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
        ),

    [_LOWER_ANSI] = LAYOUT( \
        KC_TRNS , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                    KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_ASTR, KC_TRNS, \
        KC_TRNS , KC_PLUS, KC_EQL , KC_LBRC, KC_RBRC, KC_QUES,                                    KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_MINS, KC_TRNS, \
        KC_TRNS , KC_TRNS, _CUT   , _COPY  , _PASTE , KC_TILD,                                    KC_GRV , KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
        ),

    [_RAISE] = LAYOUT( \
        KC_TRNS , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                    KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_TRNS, \
        KC_TRNS , KC_LEFT, KC_RGHT, KC_UP  , KC_DOWN, KC_F11 ,                                    KC_F12 , KC_PSCR, KC_PGUP, KC_HOME, KC_DEL , KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_PGDN, KC_END , KC_INS , KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
        ),

    [_NUM] = LAYOUT( \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                    KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
        ),

    [_SETTINGS] = LAYOUT( \
        KC_TRNS , KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS,                                    KC_TRNS, SP_GAME, SP_DV  , SP_DVAN, SP_QW  , KC_TRNS, \
        KC_TRNS , KC_TRNS, KC_TRNS ,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS                             \
        )
};

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Turns out to probably be faster than bit shifting, this mc has the memory anyway
    static char pressing_double_quote  = 0;
    static char pressing_single_quote  = 0;
    static char pressing_left_bracket  = 0;
    static char pressing_comma         = 0;
    static char pressing_dot           = 0;
    static char pressing_right_bracket = 0;
    static char pressing_semi_colon    = 0;
    static char pressing_reg_colon     = 0;
    bool pressed = record->event.pressed;
    // Synthetically modifying the shift key, has to be handled first
    if (pressing_left_bracket) {
        if (keycode == KC_LSFT && !pressed) {
        } else {
            register_code(KC_LSFT);
        }
        unregister_code(KC_NUBS);
        pressing_left_bracket = 0;
    }
    switch (keycode) {
        case SH_APST:
            if (pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    // Remapping quote to work on swedish layouts Shift held down, Shift + 2 -> Quote
                    register_code(KC_2); // Should be shifted but shift is already pressed.
                    pressing_double_quote = 1;
                } else {
                    // Remapping to single quote '
                    register_code(KC_BSLS);
                    pressing_single_quote = 1;
                }
            } else {
                if (pressing_double_quote) {
                    unregister_code(KC_2);
                    pressing_double_quote = 0;
                }
                if (pressing_single_quote) {
                    unregister_code(KC_BSLS);
                    pressing_single_quote = 0;
                }
            }
            break;
        case CM_LBR:
            if (pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    // Need to unregister and re-register shift here.
                    unregister_code(KC_LSFT);
                    register_code(KC_NUBS);
                    pressing_left_bracket = 1;
                } else {
                    register_code(KC_COMMA);
                    pressing_comma = 1;
                }
            } else {
                if (pressing_left_bracket) {
                    unregister_code(KC_NUBS);
                    pressing_left_bracket = 0;
                }
                if (pressing_comma) {
                    unregister_code(KC_COMMA);
                    pressing_comma = 0;
                }
            }
            break;
        case DT_RBR:
            if (pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_NUBS); // Should be shifted but shift is already pressed.
                    pressing_right_bracket = 1;
                } else {
                    register_code(KC_DOT);
                    pressing_dot = 1;
                }
            } else {
                if (pressing_right_bracket) {
                    unregister_code(KC_NUBS);
                    pressing_right_bracket = 0;
                }
                if (pressing_dot) {
                    unregister_code(KC_DOT);
                    pressing_dot = 0;
                }
            }
            break;
        case SCRC:
            if (pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_DOT); // Should be shifted but shift is already pressed
                    pressing_reg_colon = 1;
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_COMMA);
                    pressing_semi_colon = 1;
                }
            } else {
                if (pressing_reg_colon) {
                    unregister_code(KC_DOT);
                    pressing_reg_colon = 0;
                }

                if (pressing_semi_colon) {
                    unregister_code(KC_COMMA);
                    unregister_code(KC_LSFT);
                    pressing_semi_colon = 0;
                }
            }
            break;
        case SP_DV:
            if (pressed) {
                set_single_persistent_default_layer(_DVORAK);
                oled_display_update_layer(_DVORAK);
            }
            break;
        case SP_DVAN:
            if (pressed) {
                set_single_persistent_default_layer(_DVORAK_ANSI);
                oled_display_update_layer(_DVORAK_ANSI);
            }
            break;
        case SP_QW:
            if (pressed) {
                set_single_persistent_default_layer(_QWERTY_ANSI);
                oled_display_update_layer(_QWERTY_ANSI);
            }
            break;
        case SP_GAME:
            if (pressed) {
                set_single_persistent_default_layer(_QWERTY_GAMING);
                oled_display_update_layer(_QWERTY_GAMING);
            }
            break;
        case KC_LSFT:
            oled_display_update_shift(pressed);
            if (pressed) {
                // Synthetic shifting needs to be interrupted if shift is actually pressed.
                // We immediately stop regarding semi_colon as being pressed
                register_code(KC_LSFT);
                unregister_code(KC_COMMA);
                pressing_semi_colon = 0;
            } else {
                // Here we need to reset our shifted up versioned keycodes
                unregister_code(KC_LSFT);
                // Unregister double quote
                unregister_code(KC_2);
                pressing_double_quote = 0;

                // Unregister right bracket
                unregister_code(KC_NUBS);
                pressing_right_bracket = 0;

                // Unregister regular colon
                unregister_code(KC_DOT);
                pressing_reg_colon = 0;
                // Unregister semi colon
                unregister_code(KC_COMMA);
                pressing_semi_colon = 0;
            }
            break;
        case KC_LCTL:
        case KC_RCTL:
            oled_display_update_ctrl(pressed);
            break;
    }
    return true;
}

// Called by qmk
bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_update(index, clockwise);
    return false;
}

// Called by qmk
bool oled_task_user(void) {
    return false;
}

void keyboard_post_init_user(void) {
    // Set defaults on oled display
    oled_display_update_layer(_DVORAK);
    oled_display_update_shift(false);
    oled_display_update_ctrl(false);
    oled_worker_start();
}