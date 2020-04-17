// Default layout for Zeal60
#include QMK_KEYBOARD_H

enum unicode_names {
    C_CAPS,
	C_MIN,
	N_CAPS,
    N_MIN
};

const uint32_t PROGMEM unicode_map[] = {
	[C_CAPS] = 0xC7, 	// Ç
    [C_MIN] = 0xE7, 	// ç
	[N_CAPS] = 0xD1, 	// Ñ
    [N_MIN] = 0xF1, 	// ñ
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Default layer
[0] = LAYOUT_60_ansi(
	
	KC_ESC,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,		KC_EQL,		KC_BSPC,
	KC_TAB,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_LBRC,		KC_RBRC,	KC_BSLS,
	KC_DEL,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,	KC_QUOT,		KC_ENT,
	KC_LSFT,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	RSFT_T(KC_DEL),
	KC_LCTL,	KC_LGUI,	KC_LAPO,										KC_SPC,								KC_RAPC,	KC_RGUI,	MO(1),			RCTL_T(KC_CAPS)),

// Fn1 Layer
[1] = LAYOUT_60_ansi(

	KC_GRV,		KC_F1,		KC_F2,		KC_F3,				KC_F4,		KC_F5,		KC_F6,				KC_F7,				KC_F8,				KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_DEL ,
	KC_TRNS,	KC_VOLD,	KC_UP,		KC_VOLU,			KC_MUTE,	KC_TRNS,	KC_TRNS,			KC_TRNS,			KC_TRNS,			KC_TRNS,	KC_TRNS,	KC_HOME,	KC_PGUP,	KC_TRNS,
	KC_CAPS,	KC_LEFT,	KC_DOWN,	KC_RGHT,			KC_TRNS,	KC_TRNS,	KC_TRNS,			KC_TRNS,			KC_TRNS,			KC_TRNS,	KC_END,		KC_PGDN,	KC_WREF,
	KC_TRNS,	KC_MPRV,	KC_MNXT,	XP(C_MIN,C_CAPS),	KC_TRNS, 	KC_TRNS,	XP(N_MIN,N_CAPS),	MAGIC_UNHOST_NKRO, 	MAGIC_HOST_NKRO,	BR_DEC,		BR_INC,		KC_PSCR,
	KC_TRNS,	KC_TRNS,	KC_TRNS,                            					KC_MPLY,                            						KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS),

};
