// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "keymap.h"

#ifdef LED_MATRIX_ENABLE
#include "led_matrix_custom.h"
#include "eeconfig.h"

user_config_t user_config;

extern bool edit_mode;
extern uint8_t custom_buf[CUSTOM_MODE_SIZE];

#define BLINK_LENGTH 500
uint32_t blink_timer;

//uint8_t ret = 0;
void keyboard_post_init_user(void) {
    eeconfig_read_user_datablock(&user_config.raw, 0, EECONFIG_USER_DATA_SIZE);

    blink_timer = timer_read32() + BLINK_LENGTH;
}

void eeconfig_init_user(void) {
    memset(user_config.raw, 0, EECONFIG_USER_DATA_SIZE);
    user_config.custom_mode = MODE_2;

    eeconfig_update_user_datablock(&user_config.raw, 0, EECONFIG_USER_DATA_SIZE);
}
#endif

enum layer_names {
    BASE,
    WINLK,
    FN,
};

enum custom_keycode {
    LM_CSTM = QK_USER_0,
    LM_MOD1,
    LM_MOD2,
    LM_MOD3,
    LM_MOD4,
    LM_MOD5,
    LM_MOD6,
    LM_MOD7,
    LM_MOD8,
    LM_MOD9,
    LM_MOD0,
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
        QK_BOOT,            KC_WFAV, KC_MYCM, KC_MAIL, KC_WHOM, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, EE_CLR,
        _______, LM_MOD1,   LM_MOD2, LM_MOD3, LM_MOD4, LM_MOD5, LM_MOD6, LM_MOD7, LM_MOD8, LM_MOD9, LM_MOD0, _______, _______, _______, LM_NEXT, _______, _______, _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LM_CSTM, _______, _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                            _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          LM_BRIU,          _______, _______, _______, _______,
        _______, TG(WINLK), _______,                            _______,                            _______, _______, _______, _______, LM_SPDD, LM_BRID, LM_SPDU, _______, _______
    ),
};

#ifdef LED_MATRIX_ENABLE
#define NUM_LOCK_LED_INDEX 33
#define CAPS_LOCK_LED_INDEX 58
#define SCROLL_LOCK_LED_INDEX 14
#define WIN_LOCK_LED_INDEX 92
bool led_matrix_indicators_user() {
    //led_matrix_set_value(ret, 255);
    if (edit_mode) {
        static bool state = false;

        if (timer_expired32(timer_read32(), blink_timer)) {
            state = !state;
            
            blink_timer = timer_read32() + BLINK_LENGTH;
        }

        led_matrix_set_value(NUM_LOCK_LED_INDEX, state ? 255 : 0);
        led_matrix_set_value(CAPS_LOCK_LED_INDEX, state ? 255 : 0);
        led_matrix_set_value(SCROLL_LOCK_LED_INDEX, state ? 255 : 0);
        led_matrix_set_value(WIN_LOCK_LED_INDEX, state ? 255 : 0);
    }

    led_t state = host_keyboard_led_state();

    led_matrix_set_value(NUM_LOCK_LED_INDEX, state.num_lock ? 255 : 0);
    led_matrix_set_value(CAPS_LOCK_LED_INDEX, state.caps_lock ? 255 : 0);
    led_matrix_set_value(SCROLL_LOCK_LED_INDEX, state.scroll_lock ? 255 : 0);
    led_matrix_set_value(WIN_LOCK_LED_INDEX, layer_state_is(WINLK) ? 255 : 0);

    return true;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (edit_mode && !layer_state_is(FN) && (keycode != MO(FN) || !record->event.pressed)) {
        uint8_t index = g_led_config.matrix_co[record->event.key.row][record->event.key.col];
        custom_mode_set(custom_buf, index, custom_mode_get(custom_buf, index));
        return false;
    }

    switch (keycode) {
        case LM_CSTM:
        if (record->event.pressed) {
#ifdef LED_MATRIX_ENABLE
            led_matrix_custom();
#endif
        }
            return false;
        case LM_MOD1:
        case LM_MOD2:
        case LM_MOD3:
        case LM_MOD4:
        case LM_MOD5:
        case LM_MOD6:
        case LM_MOD7:
        case LM_MOD8:
        case LM_MOD9:
        case LM_MOD0:
            if (record->event.pressed) {
#ifdef LED_MATRIX_ENABLE
                led_matrix_custom_mode(keycode - LM_MOD1);
#endif
            }
            return false;
    }

    return true;
}
