// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "../../animations/util/direction.h"

enum layer_names {
    BASE,
    WINLK,
    FN,
};

enum custom_keycode {
    RM_LEFT = SAFE_RANGE,
    RM_MOD1,
    RM_MOD2,
    RM_MOD3,
    RM_MOD4,
    RM_MOD5,
    RM_MOD6,
    RM_MOD7,
    RM_MOD8,
    RM_MOD9,
    RM_RGHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_fullsize_ansi(
        KC_ESC,           KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCRL, KC_PAUS,
        KC_GRV,  KC_1,    KC_2,    KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP, KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN, KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                             KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,          KC_Z,    KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,            KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL, KC_LGUI, KC_LALT,                       KC_SPC,                      KC_RALT, MO(FN),  KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT
    ),
    [WINLK] = LAYOUT_fullsize_ansi(
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,          _______, _______, _______, _______,
        _______, KC_NO,   _______,                            _______,                            _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [FN] = LAYOUT_fullsize_ansi(
        _______,            KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_WHOM, KC_CALC, KC_WSCH, RM_MOD7, RM_MOD8, RM_MOD9,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_SPDD, RM_SPDU, _______, RM_MOD1, RM_MOD2, RM_MOD3, _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_MOD4, RM_MOD5, RM_MOD6, _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RM_VALU,          _______, _______, _______, _______,
        _______, TG(WINLK), _______,                            _______,                            _______, _______, _______, _______, RM_LEFT, RM_VALD, RM_RGHT, _______, _______
    ),
};

rgb_direction_t rgb_matrix_direction = RIGHT;

const uint8_t PROGMEM rgb_matrix_direction_supported_modes[] = {
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_ALL
    RGB_MATRIX_CUSTOM_CYCLE_ALL,
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_ALL
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
    RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT,
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_OUT_IN
    RGB_MATRIX_CUSTOM_CYCLE_OUT_IN,
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_OUT_IN
};
const uint8_t PROGMEM rgb_matrix_direction_supported_modes_count = sizeof(rgb_matrix_direction_supported_modes) / sizeof(rgb_matrix_direction_supported_modes[0]);

void rgb_matrix_direction_or_hue(rgb_direction_t value) {
    uint8_t mode = rgb_matrix_get_mode();
    for (uint8_t i = 0; i < pgm_read_byte(&rgb_matrix_direction_supported_modes_count); i++) {
        if (mode == pgm_read_byte(&rgb_matrix_direction_supported_modes[i])) {
            rgb_matrix_direction = value;
            return;
        }
    }

    // fallback as hue control
    switch (value) {
        case LEFT:
            rgb_matrix_decrease_hue();
            break;
        case RIGHT:
            rgb_matrix_increase_hue();
            break;
    }
}

bool rgb_matrix_run = true;

void rgb_matrix_mode_or_pause(uint8_t mode) {
    uint8_t current = rgb_matrix_get_mode();

    if (mode == current) {
        rgb_matrix_run = !rgb_matrix_run;
    } else {
        if (!rgb_matrix_run) {
            rgb_matrix_run = true;
        }
        rgb_matrix_mode(mode);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_LEFT:
            if (record->event.pressed) {
                rgb_matrix_direction_or_hue(LEFT);
            }
            return false;
        case RM_MOD1:
            if (record->event.pressed) {
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_ALL
                rgb_matrix_mode_or_pause(RGB_MATRIX_CUSTOM_CYCLE_ALL);
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_ALL
            }
            return false;
        case RM_MOD2:
            if (record->event.pressed) {
#ifdef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
                rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
#endif // ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
            }
            return false;
        case RM_MOD3:
            if (record->event.pressed) {
                // TODO: Implement effect
#ifdef ENABLE_RGB_MATRIX_
                rgb_matrix_mode(RGB_MATRIX_);
#endif // ENABLE_RGB_MATRIX_
            }
            return false;
        case RM_MOD4:
            if (record->event.pressed) {
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
                rgb_matrix_mode_or_pause(RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT);
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_LEFT_RIGHT
            }
            return false;
        case RM_MOD5:
            if (record->event.pressed) {
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
#endif // RGB_MATRIX_ENABLE
            }
            return false;
        case RM_MOD6:
            if (record->event.pressed) {
#ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
                rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
#endif // ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
            }
            return false;
        case RM_MOD7:
            if (record->event.pressed) {
                // TODO: Implement effect
#ifdef ENABLE_RGB_MATRIX_
                rgb_matrix_mode(RGB_MATRIX_);
#endif // ENABLE_RGB_MATRIX_
            }
            return false;
        case RM_MOD8:
            if (record->event.pressed) {
#ifdef ENABLE_RGB_MATRIX_CUSTOM_CYCLE_OUT_IN
                rgb_matrix_mode_or_pause(RGB_MATRIX_CUSTOM_CYCLE_OUT_IN);
#endif // ENABLE_RGB_MATRIX_CUSTOM_CYCLE_OUT_IN
            }
            return false;
        case RM_MOD9:
            if (record->event.pressed) {
                // TODO: Implement effect
#ifdef ENABLE_RGB_MATRIX_
                rgb_matrix_mode(RGB_MATRIX_);
#endif // ENABLE_RGB_MATRIX_
            }
            return false;
        case RM_RGHT:
            if (record->event.pressed) {
                rgb_matrix_direction_or_hue(RIGHT);
            }
            return false;
        default:
            break;
    }

    return true;
}
