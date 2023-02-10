
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
    #ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SPLASH
        // ## default customizable values ##
        #ifndef SOLID_REACTIVE_SPLASH_WAVE_RGB
            #define SOLID_REACTIVE_SPLASH_WAVE_RGB 0x3c1f9c  // purple-ish
        #endif

        #ifndef SOLID_REACTIVE_SPLASH_WAVE_WIDTH
            #define SOLID_REACTIVE_SPLASH_WAVE_WIDTH 75  // ~8 keys wide (including fade/dropoff)
        #endif
        // ## default customizable values ##

        RGB_MATRIX_EFFECT(SOLID_REACTIVE_SPLASH)
        #ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
            #define _MAX(a, b) ((a) > (b) ? (a) : (b))
            #define _MIN(a, b) ((a) < (b) ? (a) : (b))
            #define _CLAMP(v, min, max) (_MIN(_MAX(v, min), max))

            #define _RGBHEX_R(rgb) ((rgb) >> 16)
            #define _RGBHEX_G(rgb) (((rgb) >> 8) & 0xFF)
            #define _RGBHEX_B(rgb) ((rgb) & 0xFF)

            bool SOLID_REACTIVE_SPLASH(effect_params_t* params) {
                RGB_MATRIX_USE_LIMITS(led_min, led_max);

                RGB base_rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
                RGB wave_rgb = {
                    .r = _RGBHEX_R(SOLID_REACTIVE_SPLASH_WAVE_RGB),
                    .g = _RGBHEX_G(SOLID_REACTIVE_SPLASH_WAVE_RGB),
                    .b = _RGBHEX_B(SOLID_REACTIVE_SPLASH_WAVE_RGB)
                };

                for (uint8_t i = led_min; i < led_max; i++) {
                    RGB_MATRIX_TEST_LED_FLAGS();
                    uint8_t A          = 0;
                    uint8_t hit_count  = g_last_hit_tracker.count;
                    uint8_t wave_speed = rgb_matrix_config.speed;

                    /* result = (A * wave_color) + ((1 - A) * base_color) */
                    for (uint8_t j = 0; j < hit_count; j++) {
                        uint16_t tick             = g_last_hit_tracker.tick[j];
                        uint16_t wave_travel_dist = scale16by8(tick, qadd8(wave_speed, 1));  // a * (b/255)
                        uint16_t dx               = g_led_config.point[i].x - g_last_hit_tracker.x[j];
                        uint16_t dy               = g_led_config.point[i].y - g_last_hit_tracker.y[j];
                        uint8_t  key_dist         = sqrt16(dx * dx + dy * dy);
                        uint16_t offset           = wave_travel_dist - key_dist;

                        bool before_wave = offset > SOLID_REACTIVE_SPLASH_WAVE_WIDTH;
                        bool after_wave = wave_travel_dist < key_dist;
                        bool inside_wave = !before_wave && !after_wave;

                        if (inside_wave) {
                            A = qadd8(A, qsub8(
                                0xFF, _CLAMP(
                                    255 * offset / SOLID_REACTIVE_SPLASH_WAVE_WIDTH,
                                    0, 0xFF
                                )
                            ));
                        }
                    }

                    RGB rgb = {
                        .r = scale8(wave_rgb.r, A) + scale8(base_rgb.r, 0xFF - A),
                        .g = scale8(wave_rgb.g, A) + scale8(base_rgb.g, 0xFF - A),
                        .b = scale8(wave_rgb.b, A) + scale8(base_rgb.b, 0xFF - A),
                    };
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }

                return rgb_matrix_check_finished_leds(led_max);
            }

        #endif
    #endif
#endif
