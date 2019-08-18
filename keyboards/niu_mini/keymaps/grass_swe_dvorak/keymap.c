#include QMK_KEYBOARD_H
#include "keymap_swedish.h"

enum {
	_DVORAK      = 0, // Dvorak for Swedish QWERTY Layout, can type åäö
	_DVORAK_ANSI = 1, // Dvorak for US ANSI QWERTY Layout
	_QWERTY_ANSI = 2, // QWERTY for US ANSI QWERTY Layout
	_LOWER       = 3, // Hold layer for special characters when using Nordic layouts
	_LOWER_ANSI  = 4, // Hold layer for special characters when using ANSI layouts
	_RAISE       = 5, // Hold layer rarely used specials such as F-keys and arrows
	_WILDCARD    = 6, // Hold layer for special commands and volume/led controls
	_NUM         = 7, // Hold layer for numbers
	_SETTINGS    = 8, // Hold layer for switching keyboard settings
};

#define LOWER MO(_LOWER)
#define LOWANS MO(_LOWER_ANSI)
#define RAISE MO(_RAISE)
#define WILD MO(_WILDCARD)
#define NUM MO(_NUM)
#define SETTS MO(_SETTINGS)

#define CSE LCTL(LSFT(KC_ESC))
#define CAD LCTL(LALT(KC_DEL))
#define ALTINS LALT(KC_INS)
#define ESC_CTL MT(MOD_LCTL, KC_ESC)

#define _CUT LCTL(KC_C)
#define _COPY LCTL(KC_X)
#define _PASTE LCTL(KC_V)

enum custom_keycodes {
    SFTAPSTR = SAFE_RANGE, // '"
    COMLBR, // ,<
    DOTRBR, // .>
    SCOLCOL, // ;:
	SP_DV,
    SP_DVANS,
    SP_QW
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Dvorak NO
	 * ,-----------------------------------------------------------------------------------.
	 * | TAB  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | ESC  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |ENTER |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |SHIFT |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Ctrl |  GUI | ALT  | WILD |LOWER |    Space    |  NUM | RAISE|ALT GR|Setts | CTRL |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_DVORAK] = LAYOUT_planck_mit(
		KC_TAB,  SFTAPSTR, COMLBR,   DOTRBR,  KC_P,  KC_Y,   KC_F,  KC_G,  KC_C,    KC_R,    KC_L,    KC_BSPC,
		ESC_CTL, KC_A,     KC_O,     KC_E,    KC_U,  KC_I,   KC_D,  KC_H,  KC_T,    KC_N,    KC_S,    KC_ENT,
		KC_LSFT, SCOLCOL,  KC_Q,     KC_J,    KC_K,  KC_X,   KC_B,  KC_M,  KC_W,    KC_V,    KC_Z,    KC_LSFT,
		KC_LCTL, KC_LGUI,  KC_LALT,  WILD,    LOWER,     KC_SPC,    NUM ,  RAISE,   KC_ALGR, SETTS,   KC_RCTL
    ),

    /* Dvorak ANSI
	 * ,-----------------------------------------------------------------------------------.
	 * | TAB  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | ESC  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |ENTER |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |SHIFT |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Ctrl |  GUI | ALT  | WILD |LOWER |    Space    |  NUM | RAISE|ALT GR|Setts | CTRL |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_DVORAK_ANSI] = LAYOUT_planck_mit(
		KC_TAB,  KC_QUOT,  KC_COMM,  KC_DOT,  KC_P,  KC_Y,   KC_F,  KC_G,  KC_C,    KC_R,    KC_L,    KC_BSPC,
		ESC_CTL, KC_A,     KC_O,     KC_E,    KC_U,  KC_I,   KC_D,  KC_H,  KC_T,    KC_N,    KC_S,    KC_ENT,
		KC_LSFT, KC_SCLN,  KC_Q,     KC_J,    KC_K,  KC_X,   KC_B,  KC_M,  KC_W,    KC_V,    KC_Z,    KC_LSFT,
		KC_LCTL, KC_LGUI,  KC_LALT,  WILD,    LOWANS,    KC_SPC,    NUM ,  RAISE,   KC_ALGR, SETTS,   KC_RCTL
    ),

    /* QWERTY ANSI
	 * ,-----------------------------------------------------------------------------------.
	 * | TAB  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | ESC  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |ENTER |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   '  |SHIFT |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Ctrl |  GUI | ALT  | WILD |LOWER |    Space    |  NUM | RAISE|ALT GR|Setts | CTRL |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_QWERTY_ANSI] = LAYOUT_planck_mit(
		KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,  KC_T,   KC_Y,  KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
		ESC_CTL, KC_A,     KC_S,     KC_D,    KC_F,  KC_G,   KC_H,  KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,
		KC_LSFT, KC_Z,     KC_X,     KC_C,    KC_V,  KC_B,   KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_QUOT, KC_LSFT,
		KC_LCTL, KC_LGUI,  KC_LALT,  WILD,    LOWANS,    KC_SPC,    NUM ,  RAISE,   KC_ALGR, SETTS,   KC_RCTL
    ),
	/* Lower
	 * ,-----------------------------------------------------------------------------------.
	 * |      |  !   |  @   |   #  |   $  |   %  |   ^  |   &  |   (  |   )  |   *  |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |  +   |   =  |  [   |   ]  |   ?  |   \  |   /  |   {  |   }  |   -  |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      | Cut  | Copy | Paste|   ~  |   `  |   |  |   å  |   ä  |   ö  |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_LOWER] = LAYOUT_planck_mit(
		KC_TRNS, KC_EXLM, NO_AT  , KC_HASH, NO_DLR , KC_PERC, NO_CIRC, NO_AMPR, NO_LPRN, NO_RPRN, NO_ASTR, KC_TRNS,
		KC_TRNS, NO_PLUS, NO_EQL , NO_LBRC, NO_RBRC, NO_QUES, NO_BSLS, NO_SLSH, NO_LCBR, NO_RCBR, NO_MINS, KC_TRNS,
		KC_TRNS, KC_TRNS, _CUT   , _COPY  , _PASTE , NO_TILD, NO_GRV , NO_PIPE, NO_AA  , NO_AE  , NO_OSLH, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	/* Lower ANSI
	 * ,-----------------------------------------------------------------------------------.
	 * |      |  !   |  @   |   #  |   $  |   %  |   ^  |   &  |   (  |   )  |   *  |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |  +   |   =  |  [   |   ]  |   ?  |   \  |   /  |   {  |   }  |   -  |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      | Cut  | Copy |Paste |      |   ~  |   `  |   |  |      |      |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_LOWER_ANSI] = LAYOUT_planck_mit(
		KC_TRNS, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_LPRN, KC_RPRN, KC_ASTR, KC_TRNS,
		KC_TRNS, KC_PLUS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUES, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_MINS, KC_TRNS,
		KC_TRNS, KC_TRNS, _CUT   , _COPY  , _PASTE , KC_TILD, KC_GRV , KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	/* Raise
	 * ,-----------------------------------------------------------------------------------.
	 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      | Left |Right |  Up  | Down | F11  | F12  | Pscr | PgUp | Home | Del  |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      | PgDn | End  | Ins  |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_RAISE] = LAYOUT_planck_mit(
		KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_TRNS,
		KC_TRNS, KC_LEFT, KC_RGHT, KC_UP  , KC_DOWN, KC_F11,  KC_F12 , KC_PSCR, KC_PGUP, KC_HOME, KC_DEL , KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_END , KC_INS , KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	/* Wild
	 * ,-----------------------------------------------------------------------------------.
	 * |      | CAD  |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |AltIns|      |      | MPLY |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |CSEsc |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_WILDCARD] = LAYOUT_planck_mit(
		KC_TRNS, CAD    , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, ALTINS , KC_TRNS, KC_MPLY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, CSE    , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	/* NUM
	 * ,-----------------------------------------------------------------------------------.
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_NUM] = LAYOUT_planck_mit(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	/* SETTINGS
	 * ,-----------------------------------------------------------------------------------.
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      | DV   |DVANSI|QWANSI|      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_SETTINGS] = LAYOUT_planck_mit(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, SP_DV  , SP_DVANS,SP_QW  , KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFTAPSTR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    tap_code(KC_2);
                } else {
                    tap_code(KC_BSLS);
                }
            }
            break;
        case COMLBR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    // Need to unregister and re-register shift here.
                    unregister_code(KC_LSFT);
                    tap_code(KC_NUBS);
                    register_code(KC_LSFT);
                } else {
                    tap_code(KC_COMMA);
                }
            }
            break;
        case DOTRBR:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    tap_code(KC_NUBS); // Should be shifted but shift is already pressed.
                } else {
                    tap_code(KC_DOT);
                }
            }
            break;
        case SCOLCOL:
            if (record -> event.pressed) {
                if (keyboard_report -> mods & MOD_BIT(KC_LSFT)) {
                    tap_code(KC_DOT); // Should be shifted but shift is already pressed
                } else {
                    tap_code16(LSFT(KC_COMMA));
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
    }
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
