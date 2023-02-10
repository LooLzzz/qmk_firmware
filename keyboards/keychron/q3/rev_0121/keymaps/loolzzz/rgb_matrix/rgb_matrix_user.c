/* Copyright 2021 @ Grayson Carr
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
#include "rgb_matrix_user.h"
#include "../keymap_setup.h"
#include "../utils/utils.h"

keypos_t led_index_key_position[DRIVER_LED_TOTAL];

/*
 * Initialise RGB matrix; invert the mapping of g_led_config.matrix_co,
 * so instead of a mapping from key position to led index, we now create
 * led index to key position.
 */
void rgb_matrix_init_user() {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED)
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
        }
    }
}

void rgb_matrix_set_color_by_keycode(
    uint8_t led_min,
    uint8_t led_max,
    uint8_t layer,
    bool (*is_keycode)(uint16_t),
    uint8_t red,
    uint8_t green,
    uint8_t blue
) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode))
            rgb_matrix_set_color(i, red, green, blue);
    }
}

// Callback by QMK for advanced indicators
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);

    switch (current_layer) {
        case WIN_NORM:
        case WIN_BASE:
            if (host_keyboard_led_state().caps_lock || is_caps_word_on()) {
                // rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_caps_lock_indicator, CAPS_LOCK_INDICATOR_COLOR);

                // turn CapsLock and adjacent leds on
                for (uint8_t i = led_min; i < led_max; i++) {
                    uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i]);
                    switch (keycode) {
                        // case KC_GRV:  case KC_TAB:
                        case KC_CAPS: case CAPS_WORD:
                        // case KC_LSFT: case KC_LSPO:
                        // case KC_1:    case KC_2:       case KC_3:
                        case KC_Q:    case KC_W:       case KC_E:
                        case KC_A:    case KC_S:       case KC_D:
                        case KC_Z:    case KC_X:       case KC_C:
                            if (is_caps_word_on())
                                rgb_matrix_set_color(i, CAPS_WORD_INDICATOR_COLOR);
                            else
                                rgb_matrix_set_color(i, CAPS_LOCK_INDICATOR_COLOR);
                            break;
                    }
                }
            }
            break;

        case WIN_NORM_FN:
        case WIN_FN:
            #ifdef FN_LAYER_TRANSPARENT_KEYS_OFF
                rgb_matrix_set_color_by_keycode(led_min, led_max, current_layer, is_transparent, RGB_OFF);
            #endif
            break;
    }
}
