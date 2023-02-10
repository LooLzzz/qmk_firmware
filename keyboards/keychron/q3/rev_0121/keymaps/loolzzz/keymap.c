/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "print.h"
#include "keymap_setup.h"
#include "utils/utils.h"

#include "autocorrection/autocorrection.h"
#include "rgb_matrix/rgb_matrix_user.h"
#include "tapdance/tapdance.h"

uint8_t  _key;
uint16_t siri_prev;
bool     siri;
bool     shift_on = false;
bool     ctrl_on = false;

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint32_t PROGMEM unicode_map[] = {
    [AALPHA]   = 0x0391, [BBETA]  = 0x0392, [GGAMMA]   = 0x0393, [DDELTA] = 0x0394,
    [EEPSILON] = 0x0395, [ZZETA]  = 0x0396, [EETA]     = 0x0397, [TTHETA] = 0x0398,
    [IIOTA]    = 0x0399, [KKAPPA] = 0x039A, [LLAMBDA]  = 0x039B, [MMU]    = 0x039C,
    [NNU]      = 0x039D, [XXI]    = 0x039E, [PPI]      = 0x03A0, [RRHO]   = 0x03A1,
    [SSIGMA]   = 0x03A3, [TTAU]   = 0x03A4, [UUPSILON] = 0x03A5, [PPHI]   = 0x03A6,
    [XXHI]     = 0x03A7, [PPSI]   = 0x03A8, [OOMEGA]   = 0x03A9,

    [ALPHA]   = 0x03B1, [BETA]  = 0x03B2, [GAMMA]   = 0x03B3, [DELTA] = 0x03B4,
    [EPSILON] = 0x03B5, [ZETA]  = 0x03B6, [ETA]     = 0x03B7, [THETA] = 0x03B8,
    [IOTA]    = 0x03B9, [KAPPA] = 0x03BA, [LAMBDA]  = 0x03BB, [MU]    = 0x03BC,
    [NU]      = 0x03BD, [XI]    = 0x03BE, [PI]      = 0x03C0, [RHO]   = 0x03C1,
    [SIGMA]   = 0x03C3, [TAU]   = 0x03C4, [UPSILON] = 0x03C5, [PHI]   = 0x03C6,
    [XHI]     = 0x03C7, [PSI]   = 0x03C8, [OMEGA]   = 0x03C9,
};

key_combination_t key_comb_list[4] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}},
    {3, {KC_LSFT, KC_LCMD, KC_4}},
    {2, {KC_LWIN, KC_C}}
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_NORM] = LAYOUT_all(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,                     KC_VOLD,  KC_MUTE,  KC_VOLU,  KC_PSCR,  LT(WIN_BASE, KC_ASTR), KC_PENT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,                     KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,                    KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                              KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,                              KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  KC_APP,   MO(WIN_NORM_FN),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_NORM_FN] = LAYOUT_all(
        QK_BOOT,  EE_CLR,   _______,            KC_TASK,  KC_FLXP,  KC_BRID,  KC_BRIU,  _______,  _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  RGB_VAD,  RGB_TOG,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_all(
        KC_ESC,                 KC_F1,        KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,      KC_F12,                              KC_VOLD,  KC_MUTE,  KC_VOLU,  KC_PSCR,     LT(WIN_BASE, KC_ASTR), KC_PENT,
        KC_GRV,                 KC_1,         KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,     KC_EQL,                              KC_BSPC,  KC_INS,   KC_HOME,  TD(TD_PGUP),
        KC_TAB,                 KC_Q,         KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,     KC_RBRC,                             KC_BSLS,  KC_DEL,   KC_END,   TD(TD_PGDN),
        CAPSWRD,                KC_A,         KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                                          KC_ENT,
        TD(TD_LSHIFT),                        KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                  TD(TD_RSHIFT),                    KC_UP,
        TD(TD_LCTRL),           TD(TD_LGUI),  KC_LALT,                                KC_SPC,                                 KC_RALT,  TD(TD_APP),  MO(WIN_FN),  LT(WIN_BASE, KC_RCTL),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_all(
        QK_BOOT,  EE_CLR,            _______,           KC_TASK,               KC_FLXP,           KC_BRID,           KC_BRIU,         _______,     _______,     _______,             KC_MUTE,     KC_VOLD,  KC_VOLU,  RGB_VAD,  RGB_TOG,   RGB_VAI,   KC_MPRV,  KC_MPLY,  KC_MNXT,
        _______,  _______,           _______,           _______,               _______,           _______,           _______,         _______,     _______,     _______,             _______,     _______,  _______,  _______,  _______,   _______,   _______,
        RGB_TOG,  _______,           _______,           XP(EPSILON,EEPSILON),  XP(RHO,RRHO),      XP(THETA,TTHETA),  XP(TAU,TTAU),    _______,     _______,     XP(OMEGA,OOMEGA),    XP(PI,PPI),  _______,  _______,  _______,  _______,   _______,   _______,
        _______,  XP(ALPHA,AALPHA),  XP(SIGMA,SSIGMA),  XP(DELTA,DDELTA),      XP(PHI,PPHI),      _______,           _______,         _______,     _______,     XP(LAMBDA,LLAMBDA),  _______,     _______,            _______,
        KC_LSFT,                     _______,           XP(PSI,PPSI),          XP(GAMMA,GGAMMA),  _______,           XP(BETA,BBETA),  XP(NU,NNU),  XP(MU,MMU),  _______,             _______,     _______,                         KC_RSFT,             RGB_MOD,
        KC_LCTL,  _______,           _______,                                                                        _______,                                                                     _______,     _______,  _______,  KC_RCTL,  RGB_RMOD,  RGB_RMOD,  RGB_MOD),
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [WIN_NORM]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [WIN_NORM_FN] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
        [WIN_BASE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
        [WIN_FN]      = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    };
#endif

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
    static uint8_t  encoder_state[NUM_ENCODERS] = {0};
    static keypos_t encoder_cw[NUM_ENCODERS]    = {{ 8, 5 }};
    static keypos_t encoder_ccw[NUM_ENCODERS]  = {{ 7, 5 }};

    void encoder_action_unregister(void) {
        for (int index = 0; index < NUM_ENCODERS; ++index) {
            if (encoder_state[index]) {
                keyevent_t encoder_event = (keyevent_t) {
                    .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                    .pressed = false,
                    .time = (timer_read() | 1)
                };
                encoder_state[index] = 0;
                action_exec(encoder_event);
            }
        }
    }

    void encoder_action_register(uint8_t index, bool clockwise) {
        keyevent_t encoder_event = (keyevent_t) {
            .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
            .pressed = true,
            .time = (timer_read() | 1)
        };
        encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
        action_exec(encoder_event);
    }

    bool encoder_update_user(uint8_t index, bool clockwise) {
        encoder_action_register(index, clockwise);
        return false;
    };
#endif

void keyboard_post_init_user(void) {
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_m
}

void matrix_init_user(void) {
    rgb_matrix_init_user();
}

void matrix_scan_user(void) {
    if (siri) {
        if (timer_elapsed(siri_prev) >= 500) {
            siri = false;
            unregister_code(KC_LCMD);
            unregister_code(KC_SPACE);
        }
    }
    #if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
        encoder_action_unregister();
    #endif
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case KC_MINUS:
        case KC_EQUAL:
        case KC_GRAVE:
        case KC_BACKSLASH:
            return true;

        default:
            return false;
    }
}

bool caps_word_press_user(uint16_t keycode) {
    switch(keycode) {
        // Keycodes that continue Caps Word with shift applied
        case KC_A ... KC_Z:
        case X(AALPHA) ... X(OMEGA):
            add_weak_mods(MOD_BIT(KC_LSFT)); // apply shift to the next key
            return true;

        // Keycodes that continue Caps Word without shift applied
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
            return true;

        default:
            return false; // Deactivate Caps Word
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Auto-Correction engine
    if (!process_autocorrection(keycode, record))
        return false;

    // Enable RGB on any keypress if currently disabled after Win+L
    static bool rgb_sleep = false;
    if (rgb_sleep && record->event.pressed) {
        rgb_matrix_enable_noeeprom();
        rgb_sleep = false;
    }

    switch (keycode) {
        // ## Disable RGB on Win+L if currently enabled ##
        case KC_L:
            if (record->event.pressed && get_mods() & MOD_MASK_GUI && rgb_matrix_is_enabled()) {
                rgb_matrix_disable_noeeprom();
                rgb_sleep = true;
            }
            return true;


        // ## Custom CapsWord/CapsLock activation ##
        // Activate CapsWord normally, or CapsLock when holding shift
        case CAPSWRD:
            if ((get_mods() & MOD_MASK_SHIFT || host_keyboard_led_state().caps_lock) && record->event.pressed) {
                tap_code(KC_CAPS);
                return false;
            }
            return true;


        // ## Ignore Space Cadet(shift) when presing alt ##
        // this is mainly used for switch languages (alt+shift)
        case LT(WIN_BASE, KC_RSFT):
        case LT(WIN_BASE, KC_LSFT):
            _key = keycode == LT(WIN_BASE, KC_LSFT) ? KC_LSFT : KC_RSFT;
            if (record->event.pressed) {
                if (record->tap.count) {
                    // tap event
                    if (get_mods() & MOD_MASK_ALT) {
                        // tap event while ALT is pressed
                        register_code(_key);
                        shift_on = true;
                    }
                    else {
                        // tap event without ALT
                        tap_code16(_key == KC_LSFT ? KC_LEFT_PAREN : KC_RIGHT_PAREN);
                    }
                }
                else {
                    // hold event
                    register_code(_key);
                    shift_on = true;
                }
            }
            else if (shift_on) {
                // hold release event
                unregister_code(_key);
                shift_on = false;
            }
            return false;


        // ## Ignore Space Cadet(ctrl) when presing alt ##
        // this is mainly used for ctrl+tilde combo
        case LT(WIN_BASE, KC_RCTL):
        case LT(WIN_BASE, KC_LCTL):
            _key = keycode == LT(WIN_BASE, KC_LCTL) ? KC_LCTL : KC_RCTL;
            if (record->event.pressed) {
                if (record->tap.count) {
                    // tap event
                    tap_code16(_key == KC_LCTL ? KC_LEFT_CURLY_BRACE : KC_RIGHT_CURLY_BRACE);
                }
                else {
                    // hold event
                    register_code(_key);
                    ctrl_on = true;
                }
            }
            else if (ctrl_on) {
                // hold release event
                unregister_code(_key);
                ctrl_on = false;
            }
            return false;


        // ## Ignore TD(shift) when presing another mod ##
        // this is mainly used for switch languages (alt+shift)
        case TD(TD_LSHIFT):
        case TD(TD_RSHIFT):
            if (record->event.pressed && get_mods()) {
                register_code(keycode == TD(TD_LSHIFT) ? KC_LSHIFT : KC_RSHIFT);
                shift_on = true;
                return false;
            }
            else if (shift_on) {
                unregister_code(keycode == TD(TD_LSHIFT) ? KC_LSHIFT : KC_RSHIFT);
                shift_on = false;
                return false;
            }
        return true;



        // ## Asterisk on tap, Calc on hold ##
        case LT(WIN_BASE, KC_ASTERISK):
            if (record->event.pressed) {
                if (record->tap.count) {
                    // tap event
                    tap_code16(KC_ASTERISK);
                }
                else {
                    // hold event
                    tap_code(KC_CALCULATOR);
                }
            }
            return false;


        // ## RGB value (brightness) while no modifiers
        // ## RGB hue on CTRL
        // ## RGB saturation on SHIFT
        // ## RGB speed on ALT
        case RGB_VAI:
        case RGB_VAD:
            if (get_mods() & MOD_MASK_CTRL) {
                if (record->event.pressed) {
                    if (keycode == RGB_VAI)
                        rgb_matrix_increase_hue();
                    else
                        rgb_matrix_decrease_hue();
                }
                return false;
            }
            else if (get_mods() & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    if (keycode == RGB_VAI)
                        rgb_matrix_increase_sat();
                    else
                        rgb_matrix_decrease_sat();
                }
                return false;
            }
            else if (get_mods() & MOD_MASK_ALT) {
                if (record->event.pressed) {
                    if (keycode == RGB_VAI)
                        rgb_matrix_increase_speed();
                    else
                        rgb_matrix_decrease_speed();
                }
                return false;
            }
            else if (get_mods() & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
                if (record->event.pressed) {
                    if (keycode == RGB_VAI) {
                        // do other stuff
                    }
                    else {
                        // do other stuff
                    }
                }
                return false;
            }
            return true;


        // ## Windows specific custom keycodes ##
        case KC_TASK:
        case KC_FLXP:
        case KC_SNAP:
        case KC_CRTA:
            if (record->event.pressed)
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++)
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
            else
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++)
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
            return false;  // Skip all further processing of this key


        // ## MacOS specific custom keycodes ##
        case KC_MISSION_CONTROL:
            if (record->event.pressed)
                host_consumer_send(0x29F);
            else
                host_consumer_send(0);
            return false;  // Skip all further processing of this key
        case KC_LAUNCHPAD:
            if (record->event.pressed)
                host_consumer_send(0x2A0);
            else
                host_consumer_send(0);
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed)
                register_code(mac_keycode[keycode - KC_LOPTN]);
            else
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            return false;  // Skip all further processing of this key
        case KC_SIRI:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPACE);
                siri_prev = timer_read() | 1;
                siri = true;
            } else {
                // Do something else when release
            }
            return false;  // Skip all further processing of this key


        default:
            // Process all other keycodes normally
            break;
    }
    return true;
}
