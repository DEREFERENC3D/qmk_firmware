#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
RGB_MATRIX_EFFECT(CYCLE_LEFT_RIGHT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// these must match the x coordinates of the first and last LED
#define COLUMN_SIDE_LEFT 0
#define COLUMN_SIDE_RIGHT 240

static hsv_t CYCLE_LEFT_RIGHT_math(hsv_t hsv, uint8_t i, uint8_t time) {
    uint8_t location = g_led_config.point[i].x;

#       ifdef RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT_SIDES_RUN_SIDEWAYS
    if (location == COLUMN_SIDE_LEFT || location == COLUMN_SIDE_RIGHT) {
        location = g_led_config.point[i].y;
    }
#       endif // RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT_SIDES_RUN_SIDEWAYS

    hsv.h = location - time;

    return hsv;
}

bool CYCLE_LEFT_RIGHT(effect_params_t* params) {
    return effect_runner_i_custom(params, &CYCLE_LEFT_RIGHT_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
