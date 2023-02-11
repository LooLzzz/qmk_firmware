#include QMK_KEYBOARD_H
#include "tapdance.h"

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for LeftAlt, twice for Win+Ctrl+LeftArrow
    [TD_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, C(G(KC_LEFT))),

    // Tap once for RightAlt, twice for Win+Ctrl+RightArrow
    // [TD_APP] = ACTION_TAP_DANCE_DOUBLE(KC_APP, C(G(KC_RIGHT))),
    [TD_APP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_APP_FINISHED, TD_APP_RESET),

    // Tap once for PageUp, twice for Shift+Home
    [TD_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, C(KC_HOME)),

    // Tap once for PageDown, twice for Shift+End
    [TD_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, C(KC_END)),

    // Tap once for ')'/'(', twice for (Shift)x2, hold for Shift
    [TD_RSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_RSHIFT_FINISHED, TD_RSHIFT_RESET),
    [TD_LSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_LSHIFT_FINISHED, TD_LSHIFT_RESET),
    [TD_LCTRL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, TD_LCTRL_FINISHED,  TD_LCTRL_RESET),
};

static td_tap_t td_app_tap_state    = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_rshift_tap_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_lshift_tap_state = {.is_press_action = true, .state = TD_NONE};
static td_tap_t td_lctrl_tap_state  = {.is_press_action = true, .state = TD_NONE};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state, bool is_shift, bool is_ctrl) {
    // bool is_shift = state->keycode == TD(TD_RSHIFT) || state->keycode == TD(TD_LSHIFT);
    // bool is_ctrl = state->keycode == TD(TD_RCTRL) || state->keycode == TD(TD_LCTRL);

    if (state->count == 1) {
        if (state->interrupted && (is_shift || is_ctrl))
            return TD_SINGLE_HOLD;
        if (state->interrupted || !state->pressed)
            return TD_SINGLE_TAP;
        else
            // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
            return TD_SINGLE_HOLD;
    }
    else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted)
            return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return TD_DOUBLE_HOLD;
        else
            return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)
            return TD_TRIPLE_TAP;
        else
            return TD_TRIPLE_HOLD;
    } else
        return TD_UNKNOWN;
}

void TD_APP_FINISHED(qk_tap_dance_state_t *state, void *user_data) {
    td_app_tap_state.state = cur_dance(state, false, false);

    switch (td_app_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_APP);
            break;

        case TD_SINGLE_HOLD:
            register_code(KC_RWIN);
            break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            // LCTRL + LAPP + RIGHT_ARROW
            SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_RIGHT))));
            break;

        default:
            break;
    }
}

void TD_APP_RESET(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_app_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_RWIN);
            break;

        default:
            break;
    }
    td_app_tap_state.state = TD_NONE;
}

void TD_RSHIFT_FINISHED(qk_tap_dance_state_t *state, void *user_data) {
    td_rshift_tap_state.state = cur_dance(state, true, false);

    switch (td_rshift_tap_state.state) {
        case TD_SINGLE_TAP:
            if (get_mods())
                tap_code(KC_RSFT);
            else
                tap_code16(KC_RIGHT_PAREN);
            break;

        case TD_SINGLE_HOLD:
            register_code(KC_RSFT);
            break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_RSFT);
            tap_code(KC_RSFT);
            break;

        default:
            break;
    }
}

void TD_RSHIFT_RESET(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_rshift_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_RSFT);
            break;

        default:
            break;
    }
    td_rshift_tap_state.state = TD_NONE;
}

void TD_LSHIFT_FINISHED(qk_tap_dance_state_t *state, void *user_data) {
    td_lshift_tap_state.state = cur_dance(state, true, false);

    switch (td_lshift_tap_state.state) {
        case TD_SINGLE_TAP:
            if (get_mods())
                tap_code(KC_LSFT);
            else
                tap_code16(KC_LEFT_PAREN);
            break;

        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_LSFT);
            tap_code(KC_LSFT);
            break;

        default:
            break;
    }
}

void TD_LSHIFT_RESET(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_lshift_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;

        default:
            break;
    }
    td_lshift_tap_state.state = TD_NONE;
}

void TD_LCTRL_FINISHED(qk_tap_dance_state_t *state, void *user_data) {
    td_lctrl_tap_state.state = cur_dance(state, false, true);

    switch (td_lctrl_tap_state.state) {
        case TD_SINGLE_TAP:
            if (get_mods())
                tap_code(KC_LCTL);
            else
                tap_code16(KC_LEFT_CURLY_BRACE);
            break;

        case TD_SINGLE_HOLD:
            register_code(KC_LCTL);
            break;

        case TD_DOUBLE_TAP:
        case TD_DOUBLE_SINGLE_TAP:
            tap_code(KC_LCTL);
            tap_code(KC_LCTL);
            break;

        default:
            break;
    }
}

void TD_LCTRL_RESET(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_lctrl_tap_state.state) {
        case TD_SINGLE_HOLD:
            unregister_code(KC_LCTL);
            break;

        default:
            break;
    }
    td_lctrl_tap_state.state = TD_NONE;
}
