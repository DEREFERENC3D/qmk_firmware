#pragma once

typedef hsv_t (*dx_dy_dist_f)(hsv_t hsv, int16_t dx, int16_t dy, uint8_t dist, uint8_t time);

extern rgb_direction_t rgb_matrix_direction;
extern bool rgb_matrix_run;

bool effect_runner_dx_dy_dist_custom(effect_params_t* params, dx_dy_dist_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t speed = rgb_matrix_config.speed / 2;

    /**
     * We maintain four time variables:
     * raw_time: the unmodified time value from the global RGB timer
     * last_raw_time: the previous frame's raw_time, used to compute the delta
     * paused_time: the last time the effect was running, used to offset the delta
     * in order to prevent a "jump" on unpause
     * time: the accumulated, direction-adjusted time used by the effect
     *
     * The signed delta (diff) represents how much time has progressed since
     * the previous frame, accounting for 8-bit wrap-around. Using a signed
     * type ensures that transitions near 0/255 remain smooth instead of
     * causing large jumps, which would otherwise create visible glitches
     * in the animation. This lets us apply positive or negative deltas
     * depending on the active direction (forward or reverse) and keep
     * animations continuous even when the direction flips mid-frame.
     */
     uint8_t raw_time = scale16by8(g_rgb_timer, speed);
     static uint8_t last_raw_time = 0;
     static uint8_t paused_time = 0;
     static uint8_t time = 0;

     if (!rgb_matrix_run) {
        if (!paused_time) {
            paused_time = raw_time;
        }
        goto skip;
    }

    if (paused_time) {
        last_raw_time += raw_time - paused_time;
        paused_time = 0;
    }

    static uint8_t last_speed = 0;
    if (speed != last_speed) {
        uint8_t old_raw = scale16by8(g_rgb_timer, last_speed);
        last_raw_time += raw_time - old_raw;

        last_speed = speed;
    }

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
        int16_t dx   = g_led_config.point[i].x - k_rgb_matrix_center.x;
        int16_t dy   = g_led_config.point[i].y - k_rgb_matrix_center.y;
        uint8_t dist = sqrt16(dx * dx + dy * dy);
        rgb_t   rgb  = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, dx, dy, dist, time));
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

skip:
    return rgb_matrix_check_finished_leds(led_max);
}
