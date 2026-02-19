// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum custom_mode : uint8_t {
    MODE_1 = 0,
    MODE_2,
    MODE_3,
    MODE_4,
    MODE_5,
    MODE_6,
    MODE_7,
    MODE_8,
    MODE_9,
    MODE_0,
} custom_mode_t;

#define CUSTOM_MODE_START MODE_9

bool custom_mode_get(const uint8_t *data, uint8_t led);
void custom_mode_set(uint8_t *data, uint8_t led, bool val);

void led_matrix_custom_mode(custom_mode_t mode);
void led_matrix_custom(void);
