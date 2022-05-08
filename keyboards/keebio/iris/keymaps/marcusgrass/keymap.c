#include QMK_KEYBOARD_H
#include "keymap_nordic.h"

#define NO_AA KC_LBRC          // å
#define NO_ASTR LSFT(KC_BSLS)  // *
#define NO_UDSC LSFT(NO_MINS)  // _
#define AN_UDSC LSFT(KC_MINS)  // _

enum {
    _DVORAK        = 0, // Dvorak for Swedish QWERTY Layout, can type åäö
    _DVORAK_ANSI   = 1, // Dvorak for US ANSI QWERTY Layout
    _QWERTY_ANSI   = 2, // QWERTY for US ANSI QWERTY Layout
    _QWERTY_GAMING = 3,
    _LOWER         = 4, // Hold layer for special characters when using Nordic layouts
    _LOWER_ANSI    = 5, // Hold layer for special characters when using ANSI layouts
    _RAISE       = 6, // Hold layer rarely used specials such as F-keys and arrows
    _INTELLIJ    = 7, // Hold layer for special commands for intellij
    _NUM         = 8, // Hold layer for numbers
    _SETTINGS    = 9, // Hold layer for switching keyboard settings
};

#define LOWER MO(_LOWER)
#define LOWANS MO(_LOWER_ANSI)
#define RAISE MO(_RAISE)
#define NUM MO(_NUM)
#define SETTS MO(_SETTINGS)

#define CSE LCTL(LSFT(KC_ESC))
#define CAD LCTL(LALT(KC_DEL))
#define ALTINS LALT(KC_INS)
#define ESC_CTL MT(MOD_LCTL, KC_ESC)

#define _CUT LCTL(KC_C)
#define _COPY LCTL(KC_X)
#define _PASTE LCTL(KC_V)

// Intellij
#define IJ_BLD LCTL(KC_F9) // Build
#define IJ_RUN LSFT(KC_F10) // Run
#define IJ_RRUN LCTL(KC_F5) // Rerun
#define IJ_TEST LCTL(LSFT(KC_F10)) // Run test
#define IJ_SETT LCTL(LALT(KC_S)) // Project Settings
#define IJ_PSTR LCTL(LALT(LSFT(KC_S))) // Project structure
#define IJ_FND1 LCTL(LALT(KC_F7)) // Find usages popup
#define IJ_FND2 LALT(KC_F7) // Find usages
#define IJ_COMM LCTL(LALT(NO_SLSH)) // Comment selection
#define IJ_BCOM LCTL(LSFT(NO_SLSH)) // Block comment
#define IJ_COMP LCTL(LSFT(KC_ENT)) // Smart autocomplete
#define IJ_REFA LCTL(LSFT(LALT(KC_T))) // Refactoring opts
#define IJ_STCM LCTL(LSFT(KC_SPC)) // Smart type completion
#define IJ_FOWD LCTL(LALT(KC_RGHT)) // Go forwards
#define IJ_BACK LCTL(LALT(KC_LEFT)) // Go back
#define IJ_POPE LALT(KC_F1) // Project open (left side focus file)

enum custom_keycodes {
    SHIFT_APOSTROPHE = SAFE_RANGE, // '"
    COMMA_LEFT_BRACKET, // ,<
    DOT_RIGHT_BRACKET, // .>
    SEMI_COLON_REGULAR_COLON, // ;:
    SP_DV,
    SP_DVANS,
    SP_QW,
    SP_GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT( \
        KC_TAB  , SHIFT_APOSTROPHE, COMMA_LEFT_BRACKET  , DOT_RIGHT_BRACKET , KC_P    , KC_Y    ,                             KC_F    , KC_G    ,  KC_C   , KC_R    , KC_L    , KC_BSPC, \
        ESC_CTL , KC_A    , KC_O    , KC_E   , KC_U    , KC_I    ,                             KC_D    , KC_H    ,  KC_T   , KC_N    , KC_S    , KC_ENT , \
        KC_LSFT , SEMI_COLON_REGULAR_COLON , KC_Q    , KC_J   , KC_K    , KC_X    ,                             KC_B    , KC_M    ,  KC_W   , KC_V    , KC_Z    , KC_LSFT, \
        KC_LCTL , KC_LGUI , KC_LALT , KC_TRNS   , LOWER   , KC_SPC  , KC_LALT ,         KC_ALGR , KC_SPC  , NUM     ,  RAISE  , KC_ALGR , SETTS   , KC_RCTL, \
        KC_TRNS , NO_UDSC , KC_LSFT ,         KC_LSFT , KC_BSPC , KC_TRNS \
        ),

    [_DVORAK_ANSI] = LAYOUT( \
        KC_TAB  , KC_QUOT , KC_COMM , KC_DOT , KC_P    , KC_Y    ,                             KC_F    , KC_G    ,  KC_C   , KC_R    , KC_L    , KC_BSPC, \
        ESC_CTL , KC_A    , KC_O    , KC_E   , KC_U    , KC_I    ,                             KC_D    , KC_H    ,  KC_T   , KC_N    , KC_S    , KC_ENT , \
        KC_LSFT , KC_SCLN , KC_Q    , KC_J   , KC_K    , KC_X    ,                             KC_B    , KC_M    ,  KC_W   , KC_V    , KC_Z    , KC_LSFT, \
        KC_LCTL , KC_LGUI , KC_LALT , KC_TRNS   , LOWANS  , KC_SPC  , KC_LALT ,         KC_ALGR , KC_SPC  , NUM     ,  RAISE  , KC_ALGR , SETTS   , KC_RCTL, \
        KC_TRNS , AN_UDSC , KC_LSFT ,         KC_LSFT , KC_BSPC , KC_TRNS \
        ),

    [_QWERTY_ANSI] = LAYOUT( \
        KC_TAB  , KC_Q    , KC_W    , KC_E   , KC_R    , KC_T    ,                             KC_Y    , KC_U    ,  KC_I   , KC_O    , KC_P    , KC_BSPC, \
        ESC_CTL , KC_A    , KC_S    , KC_D   , KC_F    , KC_G    ,                             KC_H    , KC_J    ,  KC_K   , KC_L    , KC_SCLN , KC_ENT , \
        KC_LSFT , KC_Z    , KC_X    , KC_C   , KC_V    , KC_B    ,                             KC_N    , KC_M    ,  KC_COMM, KC_DOT  , KC_QUOT , KC_LSFT, \
        KC_LCTL , KC_LGUI , KC_LALT , KC_TRNS   , LOWANS  , KC_SPC  , KC_LALT ,         KC_ALGR , KC_SPC  , NUM     ,  RAISE  , KC_ALGR , SETTS   , KC_RCTL, \
        KC_TRNS , AN_UDSC , KC_LSFT ,         KC_LSFT , KC_BSPC , KC_TRNS \
        ),

    [_QWERTY_GAMING] = LAYOUT( \
        KC_TAB  , KC_1    , KC_2    , KC_3   , KC_4    , KC_5    ,                             KC_6    , KC_7    ,  KC_8   , KC_9    , KC_0    , KC_BSPC, \
        ESC_CTL , KC_T    , KC_Q    , KC_W   , KC_E    , KC_R    ,                             KC_H    , KC_J    ,  KC_K   , KC_L    , KC_SCLN , KC_ENT , \
        KC_LSFT , KC_Y    , KC_A    , KC_S   , KC_D    , KC_F    ,                             KC_N    , KC_M    ,  KC_COMM, KC_DOT  , KC_QUOT , KC_LSFT, \
        KC_LCTL , KC_Z    , KC_X    , KC_C   , KC_V    , KC_B    , KC_M   ,          KC_O    , KC_G    , KC_I    ,  RAISE  , KC_ALGR , SETTS   , KC_RCTL, \
        KC_LGUI , KC_LALT , KC_SPC ,          KC_U    , KC_P    , LOWER \
        ),

    [_LOWER] = LAYOUT( \
        KC_TRNS , KC_EXLM , NO_AT   , KC_HASH, NO_DLR  , KC_PERC ,                             NO_CIRC , NO_AMPR ,  NO_LPRN, NO_RPRN , NO_ASTR , KC_TRNS,\
        KC_TRNS , NO_PLUS , NO_EQL  , NO_LBRC, NO_RBRC , NO_QUES ,                             NO_BSLS , NO_SLSH ,  NO_LCBR, NO_RCBR , NO_MINS , KC_TRNS, \
        KC_TRNS , KC_TRNS , _CUT    , _COPY  , _PASTE  , NO_TILD ,                             NO_GRV  , NO_PIPE ,  NO_AA  , NO_OSLH , NO_AE   , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        ),

    [_LOWER_ANSI] = LAYOUT( \
        KC_TRNS , KC_EXLM , KC_AT   , KC_HASH, KC_DLR  , KC_PERC ,                             KC_CIRC , KC_AMPR ,  KC_LPRN, KC_RPRN , KC_ASTR , KC_TRNS,\
        KC_TRNS , KC_PLUS , KC_EQL  , KC_LBRC, KC_RBRC , KC_QUES ,                             KC_BSLS , KC_SLSH ,  KC_LCBR, KC_RCBR , KC_MINS , KC_TRNS, \
        KC_TRNS , KC_TRNS , _CUT    , _COPY  , _PASTE  , KC_TILD ,                             KC_GRV  , KC_PIPE ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        ),

    [_RAISE] = LAYOUT( \
        KC_TRNS , KC_F1   , KC_F2   , KC_F3  , KC_F4   , KC_F5   ,                             KC_F6   , KC_F7   ,  KC_F8  , KC_F9   , KC_F10  , KC_TRNS,\
        KC_TRNS , KC_LEFT , KC_RGHT , KC_UP  , KC_DOWN , KC_F11  ,                             KC_F12  , KC_PSCR ,  KC_PGUP, KC_HOME , KC_DEL  , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_PGDN, KC_END  , KC_INS  , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        ),

    [_INTELLIJ] = LAYOUT( \
        KC_TRNS , CAD      , IJ_COMM , IJ_BCOM, IJ_RUN  , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  IJ_BACK, IJ_FOWD , KC_TRNS , KC_TRNS,\
        CSE     , ALTINS   , IJ_BLD  , IJ_TEST, IJ_COMP , KC_TRNS ,                             KC_TRNS , IJ_STCM ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS, \
        IJ_POPE , IJ_FND1 , IJ_PSTR , IJ_SETT, IJ_RRUN , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS, \
        KC_TRNS , IJ_FND2 , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        ),

    [_NUM] = LAYOUT( \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_1    , KC_2    , KC_3   , KC_4    , KC_5    ,                             KC_6    , KC_7    ,  KC_8   , KC_9    , KC_0    , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        ),

    [_SETTINGS] = LAYOUT( \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS ,                             KC_TRNS , SP_GAME ,  SP_DV  , SP_DVANS, SP_QW   , KC_TRNS, \
        KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS ,  KC_TRNS, KC_TRNS , KC_TRNS , KC_TRNS,\
        KC_TRNS , KC_TRNS , KC_TRNS ,         KC_TRNS , KC_TRNS , KC_TRNS \
        )
};





void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}


void setBit(char* toSet, char pos) {
    *toSet |= (char)1 << pos;
}

void clearBit(char* toClear, char pos) {
    *toClear &= ~((char)1 << pos);
}

char bitSet(char toCheck, char pos) {
    return toCheck & (1 << pos);
}

char pressing_double_quote = 0;
char pressing_single_quote = 0;
char pressing_left_bracket = 0;
char pressing_comma = 0;
char pressing_dot = 0;
char pressing_right_bracket = 0;
char pressing_semi_colon = 0;
char pressing_reg_colon = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Synthetically modifying the shift key, has to be handled first
    if (pressing_left_bracket) {
        if (keycode == KC_LSFT && !(record -> event.pressed)) {

        } else {
            register_code(KC_LSFT);
        }
        unregister_code(KC_NUBS);
        pressing_left_bracket = 0;
    }
    switch (keycode) {
        case SHIFT_APOSTROPHE:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
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
        case COMMA_LEFT_BRACKET:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
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
        case DOT_RIGHT_BRACKET:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
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
        case SEMI_COLON_REGULAR_COLON:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
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
            if (record -> event.pressed) {
                set_single_persistent_default_layer(_DVORAK);
            }
            break;
        case SP_DVANS:
            if (record -> event.pressed) {
                set_single_persistent_default_layer(_DVORAK_ANSI);
            }
            break;
        case SP_QW:
            if (record -> event.pressed) {
                set_single_persistent_default_layer(_QWERTY_ANSI);
            }
            break;
        case SP_GAME:
            if (record -> event.pressed) {
                set_single_persistent_default_layer(_QWERTY_GAMING);
            }
            break;
        case KC_LSFT:
            if (record -> event.pressed) {
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
    }
    return true;
}
