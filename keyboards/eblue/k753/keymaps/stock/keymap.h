// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "led_matrix_custom.h"

#ifdef LED_MATRIX_ENABLE
#define CUSTOM_MODE_COUNT 2
#define CUSTOM_MODE_SIZE (LED_MATRIX_LED_COUNT / (sizeof(uint8_t) * 8))
#define EEPROM_CUSTOM_MODE_OFFSET 0
#define EEPROM_CUSTOM_MODE_DATA_OFFSET 1

typedef union {
    uint32_t raw[EECONFIG_USER_DATA_SIZE / 4];
    struct {
        custom_mode_t custom_mode : 8;
        uint8_t custom_mode_data[CUSTOM_MODE_COUNT][CUSTOM_MODE_SIZE];
    };
} user_config_t;
#endif
