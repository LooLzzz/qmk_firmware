#include QMK_KEYBOARD_H

bool is_caps_lock_indicator(uint16_t keycode) {
    #ifdef CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
        return (KC_A <= keycode && keycode <= KC_Z) || keycode == KC_CAPS || keycode >= QK_UNICODEMAP_PAIR;
    #else
        return keycode == KC_CAPS;
    #endif
}

bool is_transparent(uint16_t keycode) {
    return keycode == KC_TRNS;
}

bool is_not_greek(uint16_t keycode) {
    if (get_mods() & MOD_MASK_SHIFT)
        return keycode < QK_UNICODEMAP_PAIR;
    return keycode < QK_UNICODEMAP;
}
