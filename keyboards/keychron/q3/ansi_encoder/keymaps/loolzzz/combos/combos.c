#include QMK_KEYBOARD_H
#include "../keymap_setup.h"

enum combo_keycodes {
    COMBO_NEXT_SONG,
    COMBO_PREV_SONG,

    _COMBO_LEN,
};

uint16_t COMBO_LEN = _COMBO_LEN;

const uint16_t PROGMEM next_song_combo[] = {MO(WIN_BASE_FN), KC_RCTL, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM prev_song_combo[] = {MO(WIN_BASE_FN), KC_RCTL, KC_LEFT,  COMBO_END};

combo_t key_combos[] = {
    [COMBO_NEXT_SONG] = COMBO(next_song_combo, KC_MEDIA_NEXT_TRACK),
    [COMBO_PREV_SONG] = COMBO(prev_song_combo, KC_MEDIA_PREV_TRACK),
};

// void process_combo_event(uint16_t combo_index, bool pressed) {
//     uprintf("process_combo_event: %d, %d\n", combo_index, pressed);
// }
