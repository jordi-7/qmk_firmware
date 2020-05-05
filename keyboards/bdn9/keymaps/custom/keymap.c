#include QMK_KEYBOARD_H

// LED timeout setup
static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static uint8_t old_backlight_level = -1;
static uint16_t old_underglow_level = -1;
static bool led_on = true;
static uint8_t led_timeout = 10; // Minutes

//
// Keymaps
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Layer 0
    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MPLY,
        MO(1)  , KC_UP  , RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layer 1
    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),

    // Layer 2
    [2] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),

};

//
// Keyboard initialization
//
void keyboard_post_init_user(void) {
    // Wait for keyboard startup
    wait_ms(100);
    // Restore previous underglow brightness
    rgblight_sethsv(213, 255, rgblight_get_val());  
}

//
// Layer changed
//
layer_state_t layer_state_set_user(layer_state_t state) {
    
    // Color codes
    // https://github.com/qmk/qmk_firmware/blob/master/quantum/rgblight_list.h

    // Get current underglow brightness
    uint16_t underglow_brightness = rgblight_get_val();
    // Get active layer
    uint8_t layer = biton32(state);

    // Set underglow to indicate active layer
    switch (layer) {

    // Layer 0
    case 0:
        rgblight_sethsv(213, 255, underglow_brightness);
        break;

    // Layer 1
    case 1:
        rgblight_sethsv(128, 255, underglow_brightness);
        break;

    // Layer 2
    case 2:
        rgblight_sethsv(0, 0, underglow_brightness);
        break;

    }
    
    return state;
}

//
// Rotary encoder actuated
//
void encoder_update_user(uint8_t index, bool clockwise) {
    // Right rotary encoder
    if (index == 1) {

        // Layer 1
        if (IS_LAYER_ON(1)) {
            if (clockwise) SEND_STRING(SS_LCTRL(SS_TAP(X_F21))); // Left control + F21
            else SEND_STRING(SS_LCTRL(SS_TAP(X_F22))); // Left control + F22

        // Layer 2
        } else if (IS_LAYER_ON(2)) {
            if (clockwise) SEND_STRING(SS_LCTRL(SS_TAP(X_F23))); // Left control + F23
            else SEND_STRING(SS_LCTRL(SS_TAP(X_F24))); // Left control + F24
        
        // Layer 0
        } else {
            // Horizontal scroll
            if (clockwise) tap_code(KC_MS_WH_RIGHT);
            else tap_code(KC_MS_WH_LEFT);
        }

    }

    // If LEDs have been turned off, restore previous brightness
    if (led_on == false || old_backlight_level == -1) {

        if (old_backlight_level == -1) {
            // Get previous backlight brightness
            old_backlight_level = get_backlight_level();
            // Get underglow backlight brightness
            old_underglow_level = rgblight_get_val();
        }

        // Restore backlight brightness
        backlight_set(old_backlight_level);
        // Restore underglow brightness
        rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), old_underglow_level);

        led_on = true;
    }

    idle_timer = timer_read();
    halfmin_counter = 0;
}

//
// Key processing
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // Key pressed
    if (record->event.pressed) {

        // If LEDs have been turned off, restore previous brightness
        if (led_on == false || old_backlight_level == -1) {

            if (old_backlight_level == -1) {
                // Get previous backlight brightness
                old_backlight_level = get_backlight_level();
                // Get underglow backlight brightness
                old_underglow_level = rgblight_get_val();
            }

            // Restore backlight brightness
            backlight_set(old_backlight_level);
            // Restore underglow brightness
            rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), old_underglow_level);

            led_on = true;
        }

        idle_timer = timer_read();
        halfmin_counter = 0;
    }

    return true;
}

//
// Scan matrix
//
void matrix_scan_user(void) {

    if (idle_timer == 0) idle_timer = timer_read();

    if ( led_on && timer_elapsed(idle_timer) > 30000) {
        halfmin_counter++;
        idle_timer = timer_read();
    }

    // Timeout has passed
    if ( led_on && halfmin_counter >= led_timeout * 2) {

        // Get previous backlight brightness
        old_backlight_level = get_backlight_level();
        // Get underglow backlight brightness
        old_underglow_level = rgblight_get_val();

        // Turn off backlight
        backlight_set(0);
        // Decrease underglow brightness
        if (old_underglow_level > 50) rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 50);

        led_on = false;
        halfmin_counter = 0;
    }
}
