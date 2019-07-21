#include QMK_KEYBOARD_H

enum {
	_DVORAK   = 0, // Standard layer
	_LOWER    = 1, // Hold layer
	_RAISE    = 2, // Hold layer
	_WILDCARD = 3, // Oneshot layer
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define WILD OSL(_WILDCARD)
#define CSE LCTL_T(LSFT_T(KC_ESC))
#define CAD LCTL_T(LALT_T(KC_DEL))
#define ALTINS LALT_T(KC_INS)

enum unicode_names {
    ARING = 0,
    ARING_CAPS = 1,
    AUMLAUT = 2,
    AUMLAUT_CAPS = 3,
    UMLAUT = 4,
    UMLAUT_CAPS = 5,
};

const uint32_t PROGMEM unicode_map[] {
    [ARING]        = 0xE5, // å
    [ARING_CAPS]   = 0xC5, // Å
    [AUMLAUT]      = 0xE4, // ä
    [AUMLAUT_CAPS] = 0xC4, // Ä
    [UMLAUT]       = 0xF6, // ö
    [UMLAUT_CAPS]  = 0xD6, // Ö
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Layer 0
	 * ,-----------------------------------------------------------------------------------.
	 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Ctrl |  GUI | Caps |  Alt |Layer1|    Space    |Layer2|  /   | Left | Down |Right |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_DVORAK] = LAYOUT_planck_mit(
		KC_TAB,  KC_QUOTE, KC_COMMA, KC_DOT,  KC_P,  KC_Y,   KC_F,  KC_G,  KC_C,    KC_R,    KC_R,    KC_BSPC,
		KC_ESC,  KC_A,     KC_O,     KC_E,    KC_U,  KC_I,   KC_D,  KC_H,  KC_T,    KC_N,    KC_S,    KC_ENT,
		KC_LSFT, KC_SCLN,  KC_Q,     KC_J,    KC_K,  KC_X,   KC_B,  KC_M,  KC_W,    KC_V,    KC_Z,    KC_RSFT,
		KC_LCTL, KC_LGUI,  KC_LALT,  WILD,    LOWER,     KC_SPC,    RAISE, KC_ALGR, KC_LEFT, KC_DOWN, KC_RGHT
  ),

	/* Lower
	 * ,-----------------------------------------------------------------------------------.
	 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      | Vol- | Vol+ | Mute |      |      |      |  F11 |  F12 |      |      |      |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Reset|      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_LOWER] = LAYOUT_planck_mit(
		KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
		KC_TRNS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_SLSH, KC_BSLS, KC_QUES, KC_PLUS, KC_EQL,  KC_MINS, KC_TRNS,
		KC_TRNS, KC_CUT , KC_COPY, KC_PSTE, KC_TRNS, KC_TILD, KC_GRV , KC_PIPE, XP(ARING, ARING_CAPS), XP(AUMLAUT, AUMLAUT_CAPS), XP(UMLAUT, UMLAUT_CAPS), KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	/* Layer 2 (r_ Indicates RGB Controls)
	 * ,-----------------------------------------------------------------------------------.
	 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * |      |r_TOG |r_Mode|r_Hue+|r_Hue-|      |      |   -  |   =  |   [  |   ]  |  \   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * |      |BL_TOG|BL_STEP|     |      |      |      |      |      |      |      |      |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |      |      |      |      |      |      |      |      |      |      |      |      |
	 * `-----------------------------------------------------------------------------------'
	 */
	[_RAISE] = LAYOUT_planck_mit(
		KC_TRNS, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_TRNS,
		KC_TRNS, KC_F11 , KC_F12 , KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_END , KC_UP    KC_HOME, KC_DEL , KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_INS , KC_TRNS,
		RESET  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),

	[_WILDCARD] = LAYOUT_planck_mit(
		KC_TRNS, CAD    , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, ALTINS , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, CSE    , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	)
};


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
