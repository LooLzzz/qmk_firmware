## Debugging ##
CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes

## Base Configuration ##
VIA_ENABLE = yes
ENCODER_MAP_ENABLE = yes

## Keyboard Configuration ##
AUTO_SHIFT_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes
UNICODEMAP_ENABLE = yes

## RGB Matrix Configuration ##
RGB_MATRIX_CUSTOM_USER = yes
RGB_MATRIX_ENABLE = yes

## Source files ##
VPATH += keyboards/keychron/common
SRC += keychron_common.c
SRC += autocorrection/autocorrection.c
SRC += combos/combos.c
SRC += rgb_matrix/rgb_matrix_user.c
SRC += tapdance/tapdance.c
SRC += utils/utils.c
