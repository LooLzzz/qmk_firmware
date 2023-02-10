## Debugging ##
CONSOLE_ENABLE = yes
# COMMAND_ENABLE = yes

## Base Configuration ##
LTO_ENABLE = yes
VIA_ENABLE = yes

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
SRC += autocorrection/*.c
SRC += combos/*.c
SRC += rgb_matrix/*.c
SRC += tapdance/*.c
SRC += utils/*.c
