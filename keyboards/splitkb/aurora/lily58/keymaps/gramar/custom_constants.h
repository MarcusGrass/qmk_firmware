//
// Created by gramar on 3/7/24.
//

#include QMK_KEYBOARD_H
#include "keymap_nordic.h"
#ifndef QMK_FIRMWARE_CUSTOM_CONSTANTS_H
#    define QMK_FIRMWARE_CUSTOM_CONSTANTS_H
#    define NO_AA KC_LBRC         // å
#    define NO_ASTR LSFT(KC_BSLS) // *
#    define NO_UDSC LSFT(NO_MINS) // _
#    define AN_UDSC LSFT(KC_MINS) // _

#    define ESC_CTL MT(MOD_LCTL, KC_ESC)

#    define _CUT LCTL(KC_C)
#    define _COPY LCTL(KC_X)
#    define _PASTE LCTL(KC_V)

// Intellij
#    define IJ_BLD LCTL(KC_F9)             // Build
#    define IJ_RUN LSFT(KC_F10)            // Run
#    define IJ_RRUN LCTL(KC_F5)            // Rerun
#    define IJ_TEST LCTL(LSFT(KC_F10))     // Run test
#    define IJ_SETT LCTL(LALT(KC_S))       // Project Settings
#    define IJ_PSTR LCTL(LALT(LSFT(KC_S))) // Project structure
#    define IJ_FND1 LCTL(LALT(KC_F7))      // Find usages popup
#    define IJ_FND2 LALT(KC_F7)            // Find usages
#    define IJ_COMM LCTL(LALT(NO_SLSH))    // Comment selection
#    define IJ_BCOM LCTL(LSFT(NO_SLSH))    // Block comment
#    define IJ_COMP LCTL(LSFT(KC_ENT))     // Smart autocomplete
#    define IJ_REFA LCTL(LSFT(LALT(KC_T))) // Refactoring opts
#    define IJ_STCM LCTL(LSFT(KC_SPC))     // Smart type completion
#    define IJ_FOWD LCTL(LALT(KC_RGHT))    // Go forwards
#    define IJ_BACK LCTL(LALT(KC_LEFT))    // Go back
#    define IJ_POPE LALT(KC_F1)            // Project open (left side focus file)

typedef enum {
    _DVORAK        = 0, // Dvorak for Swedish QWERTY Layout, can type åäö
    _DVORAK_ANSI   = 1, // Dvorak for US ANSI QWERTY Layout
    _QWERTY_ANSI   = 2, // QWERTY for US ANSI QWERTY Layout
    _QWERTY_GAMING = 3,
    _LOWER         = 4, // Hold layer for special characters when using Nordic layouts
    _LOWER_ANSI    = 5, // Hold layer for special characters when using ANSI layouts
    _RAISE         = 6, // Hold layer rarely used specials such as F-keys and arrows
    _NUM           = 7, // Hold layer for numbers
    _SETTINGS      = 8, // Hold layer for switching keyboard settings
} kb_layers;

typedef enum {
    // ShiftApostrophe
    SH_APST = SAFE_RANGE, // '"
    // Comma left bracket
    CM_LBR, // ,<
    // Dot, Right bracket
    DT_RBR, // .>
    // SEMI COLON REG COLON
    SCRC, // ;:
    SP_DV,
    SP_DVAN,
    SP_QW,
    SP_GAME,
    SP_LO,
    SP_LOAN,
    SP_RA,
    SP_NUM,
    SP_SETT,
} custom_keycodes;
#endif // QMK_FIRMWARE_CUSTOM_CONSTANTS_H
