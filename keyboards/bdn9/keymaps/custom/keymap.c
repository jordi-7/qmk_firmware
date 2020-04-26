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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MUTE, KC_HOME, KC_MPLY,
        MO(1)  , KC_UP  , RGB_MOD,
        KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),

    [2] = LAYOUT(
        RESET  , BL_STEP, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        KC_MPRV, KC_END , KC_MNXT
    ),

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 1) {

        if (!IS_LAYER_ON(1) && !IS_LAYER_ON(2)) {
            if (clockwise) tap_code(KC_MS_WH_RIGHT);
            else tap_code(KC_MS_WH_LEFT);
        }

        if (IS_LAYER_ON(1)) {
            if (clockwise) SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_F21))));
            else SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_F22))));
        }

        if (IS_LAYER_ON(2)) {
            if (clockwise) SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_F23))));
            else SEND_STRING(SS_LCTRL(SS_LSFT(SS_TAP(X_F24))));
        }

    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {

        case 0:
            rgblight_setrgb(255, 0, 190);
            break;

        case 1:
            rgblight_setrgb(0, 170, 255);
            break;

        case 2:
            rgblight_setrgb(RGB_WHITE);
            break;

        default:
            rgblight_setrgb(255, 0, 190);
            break;

        }
        
    return state;

}
