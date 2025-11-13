#pragma once
#include "../util/direction.h"

typedef hsv_t (*i_f)(hsv_t hsv, uint8_t i, uint8_t time);

extern rgb_direction_t rgb_matrix_direction;

bool effect_runner_i_custom(effect_params_t* params, i_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    /**
     * We maintain three time variables:
     *   - raw_time: the unmodified time value from the global RGB timer
     *   - last_raw_time: the previous frame's raw_time, used to compute the delta
     *   - time: the accumulated, direction-adjusted time used by the effect
     *
     * The signed delta (diff) represents how much time has progressed since
     * the previous frame, accounting for 8-bit wrap-around. Using a signed
     * type ensures that transitions near 0/255 remain smooth instead of
     * causing large jumps, which would otherwise create visible glitches
     * in the animation. This lets us apply positive or negative deltas
     * depending on the active direction (forward or reverse) and keep
     * animations continuous even when the direction flips mid-frame.
     */
    uint8_t speed = qadd8(rgb_matrix_config.speed / 4, 1);
    uint8_t raw_time = scale16by8(g_rgb_timer, speed);
    static uint8_t last_raw_time = 0;
    static uint8_t time = 0;

     int8_t diff = (int8_t)(raw_time - last_raw_time);

     switch (rgb_matrix_direction) {
        case LEFT:
            time -= diff;
            break;
        case RIGHT:
            time += diff;
            break;
    }
    
    last_raw_time = raw_time;

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_t rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}