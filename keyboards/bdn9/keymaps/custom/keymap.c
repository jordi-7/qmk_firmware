/* Copyright 2019 Danny Nguyen <danny@keeb.io>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

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
    // Het active layer
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
}
