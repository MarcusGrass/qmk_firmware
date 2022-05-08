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
    SFTAPSTR = SAFE_RANGE, // '"
    COMLBR, // ,<
    DOTRBR, // .>
    SCOLCOL, // ;:
    TOG_LCK,
    SP_DV,
    SP_DVANS,
    SP_QW,
    SP_GAME
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DVORAK] = LAYOUT( \
        KC_TAB  , SFTAPSTR, COMLBR  , DOTRBR , KC_P    , KC_Y    ,                             KC_F    , KC_G    ,  KC_C   , KC_R    , KC_L    , KC_BSPC, \
        ESC_CTL , KC_A    , KC_O    , KC_E   , KC_U    , KC_I    ,                             KC_D    , KC_H    ,  KC_T   , KC_N    , KC_S    , KC_ENT , \
        KC_LSFT , SCOLCOL , KC_Q    , KC_J   , KC_K    , KC_X    ,                             KC_B    , KC_M    ,  KC_W   , KC_V    , KC_Z    , KC_LSFT, \
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

char opts = 0;
char tog = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (bitSet(opts, 6)) {
        if (keycode == KC_LSFT && !(record -> event.pressed)) {

        } else {
            register_code(KC_LSFT);
        }
        unregister_code(KC_NUBS);
        clearBit(&opts, 6);
    }
    switch (keycode) {
        case SFTAPSTR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_2); // Should be shifted but shift is already pressed.
                    setBit(&opts, 0);
                } else {
                    register_code(KC_BSLS);
                    setBit(&opts, 1);
                }
            } else {
                if (bitSet(opts, 0)) {
                    unregister_code(KC_2);
                    clearBit(&opts, 0);
                }
                if (bitSet(opts, 1)) {
                    unregister_code(KC_BSLS);
                    clearBit(&opts, 1);
                }
            }
            break;
        case COMLBR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    // Need to unregister and re-register shift here.
                    unregister_code(KC_LSFT);
                    register_code(KC_NUBS);
                    setBit(&opts, 6);
                } else {
                    register_code(KC_COMMA);
                    setBit(&opts, 7);
                }
            } else {
                if (bitSet(opts, 6)) {
                    unregister_code(KC_NUBS);
                    clearBit(&opts, 6);
                }
                if (bitSet(opts, 7)) {
                    unregister_code(KC_COMMA);
                    clearBit(&opts, 7);
                }
            }
            break;
        case DOTRBR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_NUBS); // Should be shifted but shift is already pressed.
                    setBit(&opts, 2);
                } else {
                    register_code(KC_DOT);
                    setBit(&opts, 3);
                }
            } else {
                if (bitSet(opts, 2)) {
                    unregister_code(KC_NUBS);
                    clearBit(&opts, 2);
                }
                if (bitSet(opts, 3)) {
                    unregister_code(KC_DOT);
                    clearBit(&opts, 3);
                }
            }
            break;
        case SCOLCOL:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    register_code(KC_DOT); // Should be shifted but shift is already pressed
                    setBit(&opts, 4);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_COMMA);
                    setBit(&opts, 5);
                }
            } else {
                if (bitSet(opts, 4)) {
                    unregister_code(KC_DOT);
                    clearBit(&opts, 4);
                }

                if (bitSet(opts, 5)) {
                    unregister_code(KC_COMMA);
                    unregister_code(KC_LSFT);
                    clearBit(&opts, 5);
                }
            }
            break;
        case TOG_LCK:
            if (record -> event.pressed) {
                if (bitSet(tog, 0)) {
                    unregister_code(KC_BTN1);
                    clearBit(&tog, 0);
                } else {
                    register_code(KC_BTN1);
                    setBit(&tog, 0);
                }
            }
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
                register_code(KC_LSFT);
                unregister_code(KC_COMMA);
                clearBit(&opts, 5);

            } else {
                unregister_code(KC_LSFT);
                // Unregister first special
                unregister_code(KC_2);
                clearBit(&opts, 0);

                // Unregister second special
                unregister_code(KC_NUBS);
                clearBit(&opts, 2);

                // Unregister third special
                unregister_code(KC_DOT);
                clearBit(&opts, 4);
                unregister_code(KC_COMMA);
                clearBit(&opts, 5);
            }
            break;
    }
    return true;
}
