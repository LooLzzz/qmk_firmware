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

#pragma once
#include QMK_KEYBOARD_H

// clang-format off

enum layers {
    WIN_NORM,
    WIN_NORM_FN,
    WIN_BASE,
    WIN_FN,
};

enum custom_keycodes {
    KC_MISSION_CONTROL = SAFE_RANGE,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_SIRI,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_SCREEN_SHOT,
    KC_CORTANA,
};
typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[3];
} key_combination_t;

#define MOD_MASK_RALT MOD_BIT(KC_RALT)
#define MOD_MASK_LALT MOD_BIT(KC_LALT)

#define KC_MCTL  KC_MISSION_CONTROL
#define KC_LPAD  KC_LAUNCHPAD
#define KC_TASK  KC_TASK_VIEW
#define KC_FLXP  KC_FILE_EXPLORER
#define KC_SNAP  KC_SCREEN_SHOT
#define KC_CRTA  KC_CORTANA

enum unicode_names {
    AALPHA, BBETA, GGAMMA, DDELTA, EEPSILON, ZZETA, EETA, TTHETA, IIOTA, KKAPPA,
    LLAMBDA, MMU, NNU, XXI, PPI, RRHO, SSIGMA, TTAU, UUPSILON, PPHI, XXHI, PPSI, OOMEGA,

    ALPHA, BETA, GAMMA, DELTA, EPSILON, ZETA, ETA, THETA, IOTA, KAPPA,
    LAMBDA, MU, NU, XI, PI, RHO, SIGMA, TAU, UPSILON, PHI, XHI, PSI, OMEGA,
};

// clang-format on
