#pragma once

// Space Cadet config
// #define LCPO_KEYS KC_LCTL, KC_LSFT, KC_LBRC
// #define RCPC_KEYS KC_RCTL, KC_RSFT, KC_RBRC

// AutoShift config, keep only numrow keys
#define NO_AUTO_SHIFT_ALPHA
#define NO_AUTO_SHIFT_SPECIAL

// Tap-Hold config
#define IGNORE_MOD_TAP_INTERRUPT
#define HOLD_ON_OTHER_KEY_PRESS

// Tap Dance config
#define TAPPING_TERM 140
// #define TAPPING_TERM_PER_KEY

// Combos config
// #define COMBO_MUST_HOLD_PER_COMBO

// Unicode config
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE

/* RGB Matrix Configuration */
#ifdef RGB_MATRIX_ENABLE
    #define RGB_DISABLE_WHEN_USB_SUSPENDED
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS

    #define CAPS_WORD_INDICATOR_COLOR 0x82, 0x54, 0xCC  // light-ish purple
    #define CAPS_LOCK_INDICATOR_COLOR 0xFF, 0x00, 0x00  // light-ish orange
    #define CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
    #define FN_LAYER_TRANSPARENT_KEYS_OFF

    #define ENABLE_RGB_MATRIX_SOLID_COLOR                 // Static single hue no speed support
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS                 // Static dual hue speed is hue for secondary hue
    #undef  ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN            // Static gradient top to bottom speed controls how much gradient changes
    #undef  ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT         // Static gradient left to right speed controls how much gradient changes
    #undef  ENABLE_RGB_MATRIX_BREATHING                   // Single hue brightness cycling animation
    #undef  ENABLE_RGB_MATRIX_BAND_SAT                    // Single hue band fading saturation scrolling left to right
    #undef  ENABLE_RGB_MATRIX_BAND_VAL                    // Single hue band fading brightness scrolling left to right
    #undef  ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT           // Single hue 3 blade spinning pinwheel fades saturation
    #undef  ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL           // Single hue 3 blade spinning pinwheel fades brightness
    #undef  ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT             // Single hue spinning spiral fades saturation
    #undef  ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL             // Single hue spinning spiral fades brightness
    #undef  ENABLE_RGB_MATRIX_CYCLE_ALL                   // Full keyboard solid hue cycling through full gradient
    #undef  ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT            // Full gradient scrolling left to right
    #undef  ENABLE_RGB_MATRIX_CYCLE_UP_DOWN               // Full gradient scrolling top to bottom
    #undef  ENABLE_RGB_MATRIX_CYCLE_OUT_IN                // Full gradient scrolling out to in
    #undef  ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL           // Full dual gradients scrolling out to in
    #undef  ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON      // Full gradent Chevron shapped scrolling left to right
    #undef  ENABLE_RGB_MATRIX_CYCLE_PINWHEEL              // Full gradient spinning pinwheel around center of keyboard
    #undef  ENABLE_RGB_MATRIX_CYCLE_SPIRAL                // Full gradient spinning spiral around center of keyboard
    #undef  ENABLE_RGB_MATRIX_DUAL_BEACON                 // Full gradient spinning around center of keyboard
    #undef  ENABLE_RGB_MATRIX_RAINBOW_BEACON              // Full tighter gradient spinning around center of keyboard
    #undef  ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS           // Full dual gradients spinning two halfs of keyboard
    #undef  ENABLE_RGB_MATRIX_RAINDROPS                   // Randomly changes a single key's hue
    #undef  ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS         // Randomly changes a single key's hue and saturation
    #undef  ENABLE_RGB_MATRIX_HUE_BREATHING               // Hue shifts up a slight ammount at the same time then shifts back
    #undef  ENABLE_RGB_MATRIX_HUE_PENDULUM                // Hue shifts up a slight ammount in a wave to the right then back to the left
    #undef  ENABLE_RGB_MATRIX_HUE_WAVE                    // Hue shifts up a slight ammount and then back down in a wave to the right
    #undef  ENABLE_RGB_MATRIX_PIXEL_FRACTAL               // Single hue fractal filled keys pulsing horizontally out to edges
    #undef  ENABLE_RGB_MATRIX_PIXEL_FLOW                  // Pulsing RGB flow along LED wiring with random hues
    #undef  ENABLE_RGB_MATRIX_PIXEL_RAIN                  // Randomly light keys with random hues
    #define ENABLE_RGB_MATRIX_TYPING_HEATMAP              // How hot is your WPM!
    #define ENABLE_RGB_MATRIX_DIGITAL_RAIN                // That famous computer simulation
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE       // Pulses keys hit to hue & value then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE              // Static single hue, pulses keys hit to shifted hue then fades to current hue
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE         // Hue & value pulse near a single key hit then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE    // Hue & value pulse near multiple key hits then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS        // Hue & value pulse the same column and row of a single key hit then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS   // Hue & value pulse the same column and row of multiple key hits then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS        // Hue & value pulse away on the same column and row of a single key hit then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS   // Hue & value pulse away on the same column and row of multiple key hits then fades value out
    #undef  ENABLE_RGB_MATRIX_SPLASH                      // Full gradient & value pulse away from a single key hit then fades value out
    #undef  ENABLE_RGB_MATRIX_MULTISPLASH                 // Full gradient & value pulse away from multiple key hits then fades value out
    #undef  ENABLE_RGB_MATRIX_SOLID_SPLASH                // Hue & value pulse away from a single key hit then fades value out
    #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH           // Hue & value pulse away from multiple key hits then fades value out
    #undef  ENABLE_RGB_MATRIX_EFFECT_MAX

    // Custom RGB animations
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SPLASH  // Static single hue, value pulse away from multiple key hits then fades value out
                                                     // The animation uses these two defines in order to allow customization:

    // #define SOLID_REACTIVE_SPLASH_WAVE_RGB 0x3C1F9C  // purple-ish
    #define SOLID_REACTIVE_SPLASH_WAVE_RGB 0xE6CD12  // light yellow-ish
    #define SOLID_REACTIVE_SPLASH_WAVE_WIDTH 50      // ~4 keys wide

#endif
