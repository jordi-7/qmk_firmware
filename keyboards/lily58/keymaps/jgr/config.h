#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFC51
#define PRODUCT_ID      0x0058 
#define DEVICE_VER      0x0100
#define MANUFACTURER    F_YUUCHI
#define PRODUCT         Lily58
#define DESCRIPTION     Lily58 is 6×4+5keys column-staggered split keyboard.

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS { F6, F7, B1, B3, B2, B6 }


/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGBLIGHT_SPLIT
#define RGB_DI_PIN D3
#define RGBLED_NUM 28    // Number of LEDs
#define RGBLED_SPLIT { 14, 14 }
/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }

#define EE_HANDS
#define USE_SERIAL_PD2

#define TAPPING_TERM_PER_KEY
#if defined(RGBLIGHT_ENABLE)
#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 10
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_LIMIT_VAL 255
#endif

// Enable lighting layers
#define RGBLIGHT_LAYERS

// Swap encoder A & B pad definitions
#define ENCODER_DIRECTION_FLIP

#define OLED_TIMEOUT 600000 // 10 minutes
