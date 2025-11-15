#ifdef ENABLE_RGB_MATRIX_CUSTOM_RAINBOW_WAVE
RGB_MATRIX_EFFECT(RAINBOW_WAVE)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t RAINBOW_WAVE_math(hsv_t hsv, uint8_t i, uint8_t time) {
    hsv.h = (g_led_config.point[i].x / 8) - time;
    return hsv;
}

bool RAINBOW_WAVE(effect_params_t* params) {
    return effect_runner_i_custom(params, &RAINBOW_WAVE_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_CUSTOM_RAINBOW_WAVE
