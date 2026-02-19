// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "led_matrix_custom.h"
#include <stdbool.h>
#include <led_matrix.h>
#include <eeconfig.h>
#include "keymap.h"

extern user_config_t user_config;

bool edit_mode = false;
uint8_t custom_buf[CUSTOM_MODE_SIZE] = {1};

bool custom_mode_get(const uint8_t *data, uint8_t led) {
    if (led >= LED_MATRIX_LED_COUNT) return false;

    uint8_t byte_idx = led / (sizeof(uint8_t)*8);
    uint8_t bit_idx = led % (sizeof(uint8_t)*8);

    uint8_t byte = data[byte_idx];
    uint8_t bit = byte & (1 << bit_idx);

    return bit;
}

void custom_mode_set(uint8_t *data, uint8_t led, bool val) {
    if (led >= LED_MATRIX_LED_COUNT) return;

    uint8_t byte_idx = led / (sizeof(uint8_t)*8);
    uint8_t bit_idx = led % (sizeof(uint8_t)*8);

    if (val) {
        data[byte_idx] |= (1 << bit_idx);
    } else {
        data[byte_idx] &= ~(1 << bit_idx);
    }
}

void led_matrix_custom_mode(custom_mode_t mode) {
    if (edit_mode) {
        edit_mode = false;
        memset(custom_buf, 0, CUSTOM_MODE_SIZE);
    }

    bool set = false;
    if (user_config.custom_mode != mode) {
        set = true;
        user_config.custom_mode = mode;
    }
    
    if (led_matrix_get_mode() != LED_MATRIX_CUSTOM_SOLID_PARTIAL)
        led_matrix_mode(LED_MATRIX_CUSTOM_SOLID_PARTIAL);

    if (set)
        eeconfig_update_user_datablock(&user_config.raw, 0, 1);
}

void led_matrix_custom(void) {
    if (led_matrix_get_mode() != LED_MATRIX_CUSTOM_SOLID_PARTIAL) {
        user_config.custom_mode = MODE_1;
        led_matrix_mode(LED_MATRIX_CUSTOM_SOLID_PARTIAL);
        eeconfig_update_user_datablock(&user_config.raw, 0, 1);
    } else if (user_config.custom_mode == MODE_9 || user_config.custom_mode == MODE_0) {
        if (edit_mode) {
            memcpy(user_config.custom_mode_data[user_config.custom_mode-CUSTOM_MODE_START], custom_buf, CUSTOM_MODE_SIZE);
            edit_mode = false;

            // cleanup
            memset(custom_buf, 0, CUSTOM_MODE_SIZE);
            eeconfig_update_user_datablock(&user_config.raw, 0, EECONFIG_USER_DATA_SIZE);
        } else {
            edit_mode = true;
        }
    }
}
