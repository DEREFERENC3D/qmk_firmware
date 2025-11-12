// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include <SN32F260.h>

void keyboard_post_init_kb(void) {
    /**
     * Some keys (Print Screen, home, end, ...) are connected to the MCU in a "seventh row",
     * to lower the amount of column pins needed for just a few keys in a few rows.
     * This pin on the SN32F268 has a shared function - it functions as SWD by default,
     * but can be used as GPIO instead, if SWD is disabled. The stock firmware does this,
     * and we have to as well, in order to make those keys work.
     */
     SN_SYS0->SWDCTRL_b.SWDDIS = 1;
}

#ifdef RGB_MATRIX_ENABLE
/**
 * LED pinout:
 * _______
 * | | | |
 * R U B G
 * Green and Blue are swapped on the left and right side columns
 *
 * example - side LED top row (marked EC5 on the board):
 *  _____________
 *  |   |   |   |
 * CA7 CB1 CA8 CA9
 * CB1 is powering the LED (connected to its anode) in the "I" column of the matrix
 * (refer to the page in the document mentioned by the SLED1734X driver)
 * LED is connected the chip closest to it, so index 1
 * => LED config: {1, CA7_I, CA8_I, CA9_I}
 *
 * side LED 2nd top row (EC4):
 *  _____________
 *  |   |   |   |
 * CB1 CB4 CB2 CB3
 * => LED config: {1, CB1_L, CB2_L, CB3_L}
 */

// driver index = which one of the I2C chips the LED is connected to
// SLED1734X_I2C_ADDRESS_1 => 0
// SLED1734X_I2C_ADDRESS_2 => 1
const sled1734x_register_t PROGMEM g_sled1734x_registers[SLED1734X_DRIVER_COUNT][SLED1734X_PWM_REGISTER_COUNT] = {
    [0] = {
        // default value: NO_LED
        [0 ... SLED1734X_PWM_REGISTER_COUNT - 1] = { .led_index = NO_LED, .color_channel = RED },

        // F11
        [CB4_A] = {.led_index = 12, .color_channel = RED},
        [CB5_A] = {.led_index = 12, .color_channel = GREEN},
        [CB6_A] = {.led_index = 12, .color_channel = BLUE},

        // F12
        [CB4_B] = {.led_index = 13, .color_channel = RED},
        [CB5_B] = {.led_index = 13, .color_channel = GREEN},
        [CB6_B] = {.led_index = 13, .color_channel = BLUE},

        // Print Screen
        [CB4_C] = {.led_index = 14, .color_channel = RED},
        [CB5_C] = {.led_index = 14, .color_channel = GREEN},
        [CB6_C] = {.led_index = 14, .color_channel = BLUE},
        // Scroll Lock
        [CB4_D] = {.led_index = 15, .color_channel = RED},
        [CB5_D] = {.led_index = 15, .color_channel = GREEN},
        [CB6_D] = {.led_index = 15, .color_channel = BLUE},
        // Pause Break
        [CB4_E] = {.led_index = 16, .color_channel = RED},
        [CB5_E] = {.led_index = 16, .color_channel = GREEN},
        [CB6_E] = {.led_index = 16, .color_channel = BLUE},

        // right side - row 0
        [CB1_L] = {.led_index = 17, .color_channel = RED},
        [CB2_L] = {.led_index = 17, .color_channel = BLUE},
        [CB3_L] = {.led_index = 17, .color_channel = GREEN},

        // Backspace
        [CB4_K] = {.led_index = 32, .color_channel = RED},
        [CB5_K] = {.led_index = 32, .color_channel = GREEN},
        [CB6_K] = {.led_index = 32, .color_channel = BLUE},

        // Insert
        [CB1_A] = {.led_index = 33, .color_channel = RED},
        [CB2_A] = {.led_index = 33, .color_channel = GREEN},
        [CB3_A] = {.led_index = 33, .color_channel = BLUE},
        // Home
        [CB1_B] = {.led_index = 34, .color_channel = RED},
        [CB2_B] = {.led_index = 34, .color_channel = GREEN},
        [CB3_B] = {.led_index = 34, .color_channel = BLUE},
        // Page Up
        [CB1_C] = {.led_index = 35, .color_channel = RED},
        [CB2_C] = {.led_index = 35, .color_channel = GREEN},
        [CB3_C] = {.led_index = 35, .color_channel = BLUE},

        // Num Lock
        [CB1_D] = {.led_index = 36, .color_channel = RED},
        [CB2_D] = {.led_index = 36, .color_channel = GREEN},
        [CB3_D] = {.led_index = 36, .color_channel = BLUE},
        // Num /
        [CB1_E] = {.led_index = 37, .color_channel = RED},
        [CB2_E] = {.led_index = 37, .color_channel = GREEN},
        [CB3_E] = {.led_index = 37, .color_channel = BLUE},
        // Num *
        [CB1_F] = {.led_index = 38, .color_channel = RED},
        [CB2_F] = {.led_index = 38, .color_channel = GREEN},
        [CB3_F] = {.led_index = 38, .color_channel = BLUE},
        // Num -
        [CB1_G] = {.led_index = 39, .color_channel = RED},
        [CB2_G] = {.led_index = 39, .color_channel = GREEN},
        [CB3_G] = {.led_index = 39, .color_channel = BLUE},

        // right side - row 1
        [CB1_M] = {.led_index = 40, .color_channel = RED},
        [CB2_M] = {.led_index = 40, .color_channel = BLUE},
        [CB3_M] = {.led_index = 40, .color_channel = GREEN},

        // Backslash
        [CB1_H] = {.led_index = 55, .color_channel = RED},
        [CB2_H] = {.led_index = 55, .color_channel = GREEN},
        [CB3_H] = {.led_index = 55, .color_channel = BLUE},

        // Delete
        [CB1_I] = {.led_index = 56, .color_channel = RED},
        [CB2_I] = {.led_index = 56, .color_channel = GREEN},
        [CB3_I] = {.led_index = 56, .color_channel = BLUE},
        // End
        [CA7_A] = {.led_index = 57, .color_channel = RED},
        [CA8_A] = {.led_index = 57, .color_channel = GREEN},
        [CA9_A] = {.led_index = 57, .color_channel = BLUE},
        // Page Down
        [CA7_B] = {.led_index = 58, .color_channel = RED},
        [CA8_B] = {.led_index = 58, .color_channel = GREEN},
        [CA9_B] = {.led_index = 58, .color_channel = BLUE},

        // Num 7
        [CA7_C] = {.led_index = 59, .color_channel = RED},
        [CA8_C] = {.led_index = 59, .color_channel = GREEN},
        [CA9_C] = {.led_index = 59, .color_channel = BLUE},
        // Num 8
        [CA7_D] = {.led_index = 60, .color_channel = RED},
        [CA8_D] = {.led_index = 60, .color_channel = GREEN},
        [CA9_D] = {.led_index = 60, .color_channel = BLUE},
        // Num 9
        [CA7_E] = {.led_index = 61, .color_channel = RED},
        [CA8_E] = {.led_index = 61, .color_channel = GREEN},
        [CA9_E] = {.led_index = 61, .color_channel = BLUE},
        // Num +
        [CA7_F] = {.led_index = 62, .color_channel = RED},
        [CA8_F] = {.led_index = 62, .color_channel = GREEN},
        [CA9_F] = {.led_index = 62, .color_channel = BLUE},

        // right side - row 2
        [CB1_N] = {.led_index = 63, .color_channel = RED},
        [CB2_N] = {.led_index = 63, .color_channel = BLUE},
        [CB3_N] = {.led_index = 63, .color_channel = GREEN},

        // Num 4
        [CA4_A] = {.led_index = 78, .color_channel = RED},
        [CA5_A] = {.led_index = 78, .color_channel = GREEN},
        [CA6_A] = {.led_index = 78, .color_channel = BLUE},
        // Num 5
        [CA4_B] = {.led_index = 79, .color_channel = RED},
        [CA5_B] = {.led_index = 79, .color_channel = GREEN},
        [CA6_B] = {.led_index = 79, .color_channel = BLUE},
        // Num 6
        [CA4_C] = {.led_index = 80, .color_channel = RED},
        [CA5_C] = {.led_index = 80, .color_channel = GREEN},
        [CA6_C] = {.led_index = 80, .color_channel = BLUE},

        // right side - row 3
        [CB1_O] = {.led_index = 81, .color_channel = RED},
        [CB2_O] = {.led_index = 81, .color_channel = BLUE},
        [CB3_O] = {.led_index = 81, .color_channel = GREEN},

        // Arrow Up
        [CA4_G] = {.led_index = 95, .color_channel = RED},
        [CA5_G] = {.led_index = 95, .color_channel = GREEN},
        [CA6_G] = {.led_index = 95, .color_channel = BLUE},

        // Num 1
        [CA4_H] = {.led_index = 96, .color_channel = RED},
        [CA5_H] = {.led_index = 96, .color_channel = GREEN},
        [CA6_H] = {.led_index = 96, .color_channel = BLUE},
        // Num 2
        [CA4_I] = {.led_index = 97, .color_channel = RED},
        [CA5_I] = {.led_index = 97, .color_channel = GREEN},
        [CA6_I] = {.led_index = 97, .color_channel = BLUE},
        // Num 3
        [CA4_J] = {.led_index = 98, .color_channel = RED},
        [CA5_J] = {.led_index = 98, .color_channel = GREEN},
        [CA6_J] = {.led_index = 98, .color_channel = BLUE},
        // Num Enter
        [CA4_K] = {.led_index = 99, .color_channel = RED},
        [CA5_K] = {.led_index = 99, .color_channel = GREEN},
        [CA6_K] = {.led_index = 99, .color_channel = BLUE},

        // right side - row 4
        [CB1_P] = {.led_index = 100, .color_channel = RED},
        [CB2_P] = {.led_index = 100, .color_channel = BLUE},
        [CB3_P] = {.led_index = 100, .color_channel = GREEN},

        // left side - row 5
        [CA4_F] = {.led_index = 101, .color_channel = RED},
        [CA5_F] = {.led_index = 101, .color_channel = BLUE},
        [CA6_F] = {.led_index = 101, .color_channel = GREEN},

        // Ctrl
        [CA1_D] = {.led_index = 102, .color_channel = RED},
        [CA2_D] = {.led_index = 102, .color_channel = GREEN},
        [CA3_D] = {.led_index = 102, .color_channel = BLUE},
        // Win
        [CA1_E] = {.led_index = 103, .color_channel = RED},
        [CA2_E] = {.led_index = 103, .color_channel = GREEN},
        [CA3_E] = {.led_index = 103, .color_channel = BLUE},
        // Left Alt
        [CA1_F] = {.led_index = 104, .color_channel = RED},
        [CA2_F] = {.led_index = 104, .color_channel = GREEN},
        [CA3_F] = {.led_index = 104, .color_channel = BLUE},
        // Space
        [CA1_H] = {.led_index = 105, .color_channel = RED},
        [CA2_H] = {.led_index = 105, .color_channel = GREEN},
        [CA3_H] = {.led_index = 105, .color_channel = BLUE},
        // Right Alt
        [CA1_J] = {.led_index = 106, .color_channel = RED},
        [CA2_J] = {.led_index = 106, .color_channel = GREEN},
        [CA3_J] = {.led_index = 106, .color_channel = BLUE},
        // Fn
        [CA1_K] = {.led_index = 107, .color_channel = RED},
        [CA2_K] = {.led_index = 107, .color_channel = GREEN},
        [CA3_K] = {.led_index = 107, .color_channel = BLUE},
        // Right Menu
        [CA1_L] = {.led_index = 108, .color_channel = RED},
        [CA2_L] = {.led_index = 108, .color_channel = GREEN},
        [CA3_L] = {.led_index = 108, .color_channel = BLUE},
        // Right Ctrl
        [CA1_N] = {.led_index = 109, .color_channel = RED},
        [CA2_N] = {.led_index = 109, .color_channel = GREEN},
        [CA3_N] = {.led_index = 109, .color_channel = BLUE},

        // Arrow Left
        [CA1_O] = {.led_index = 110, .color_channel = RED},
        [CA2_O] = {.led_index = 110, .color_channel = GREEN},
        [CA3_O] = {.led_index = 110, .color_channel = BLUE},
        // Arrow Down
        [CA1_P] = {.led_index = 111, .color_channel = RED},
        [CA2_P] = {.led_index = 111, .color_channel = GREEN},
        [CA3_P] = {.led_index = 111, .color_channel = BLUE},
        // Arrow Right
        [CA4_L] = {.led_index = 112, .color_channel = RED},
        [CA5_L] = {.led_index = 112, .color_channel = GREEN},
        [CA6_L] = {.led_index = 112, .color_channel = BLUE},

        // Num 0
        [CA4_M] = {.led_index = 113, .color_channel = RED},
        [CA5_M] = {.led_index = 113, .color_channel = GREEN},
        [CA6_M] = {.led_index = 113, .color_channel = BLUE},
        // Num .
        [CA4_N] = {.led_index = 114, .color_channel = RED},
        [CA5_N] = {.led_index = 114, .color_channel = GREEN},
        [CA6_N] = {.led_index = 114, .color_channel = BLUE},

        // right side - row 5
        [CA4_O] = {.led_index = 115, .color_channel = RED},
        [CA5_O] = {.led_index = 115, .color_channel = BLUE},
        [CA6_O] = {.led_index = 115, .color_channel = GREEN},

        // right side - row 6
        [CA4_P] = {.led_index = 117, .color_channel = RED},
        [CA5_P] = {.led_index = 117, .color_channel = BLUE},
        [CA6_P] = {.led_index = 117, .color_channel = GREEN},
    },
    [1] = {
        // default value: NO_LED
        [0 ... SLED1734X_PWM_REGISTER_COUNT - 1] = { .led_index = NO_LED, .color_channel = RED },

        // left side - row 0
        [CA7_I] = {.led_index = 0, .color_channel = RED},
        [CA8_I] = {.led_index = 0, .color_channel = BLUE},
        [CA9_I] = {.led_index = 0, .color_channel = GREEN},

        // ESC
        [CB4_A] = {.led_index = 1, .color_channel = RED},
        [CB5_A] = {.led_index = 1, .color_channel = GREEN},
        [CB6_A] = {.led_index = 1, .color_channel = BLUE},

        // F1
        [CB4_B] = {.led_index = 2, .color_channel = RED},
        [CB5_B] = {.led_index = 2, .color_channel = GREEN},
        [CB6_B] = {.led_index = 2, .color_channel = BLUE},
        // F2
        [CB4_C] = {.led_index = 3, .color_channel = RED},
        [CB5_C] = {.led_index = 3, .color_channel = GREEN},
        [CB6_C] = {.led_index = 3, .color_channel = BLUE},
        // F3
        [CB4_D] = {.led_index = 4, .color_channel = RED},
        [CB5_D] = {.led_index = 4, .color_channel = GREEN},
        [CB6_D] = {.led_index = 4, .color_channel = BLUE},
        // F4
        [CB4_E] = {.led_index = 5, .color_channel = RED},
        [CB5_E] = {.led_index = 5, .color_channel = GREEN},
        [CB6_E] = {.led_index = 5, .color_channel = BLUE},

        // F5
        [CB4_F] = {.led_index = 6, .color_channel = RED},
        [CB5_F] = {.led_index = 6, .color_channel = GREEN},
        [CB6_F] = {.led_index = 6, .color_channel = BLUE},
        // F6
        [CB4_G] = {.led_index = 7, .color_channel = RED},
        [CB5_G] = {.led_index = 7, .color_channel = GREEN},
        [CB6_G] = {.led_index = 7, .color_channel = BLUE},
        // F7
        [CB4_H] = {.led_index = 8, .color_channel = RED},
        [CB5_H] = {.led_index = 8, .color_channel = GREEN},
        [CB6_H] = {.led_index = 8, .color_channel = BLUE},
        // F8
        [CB4_I] = {.led_index = 9, .color_channel = RED},
        [CB5_I] = {.led_index = 9, .color_channel = GREEN},
        [CB6_I] = {.led_index = 9, .color_channel = BLUE},

        // F9
        [CB4_J] = {.led_index = 10, .color_channel = RED},
        [CB5_J] = {.led_index = 10, .color_channel = GREEN},
        [CB6_J] = {.led_index = 10, .color_channel = BLUE},
        // F10
        [CB4_K] = {.led_index = 11, .color_channel = RED},
        [CB5_K] = {.led_index = 11, .color_channel = GREEN},
        [CB6_K] = {.led_index = 11, .color_channel = BLUE},

        // left side - row 1
        [CB1_L] = {.led_index = 18, .color_channel = RED},
        [CB2_L] = {.led_index = 18, .color_channel = BLUE},
        [CB3_L] = {.led_index = 18, .color_channel = GREEN},

        // ` (grave / tilde)
        [CB1_A] = {.led_index = 19, .color_channel = RED},
        [CB2_A] = {.led_index = 19, .color_channel = GREEN},
        [CB3_A] = {.led_index = 19, .color_channel = BLUE},
        // 1
        [CB1_B] = {.led_index = 20, .color_channel = RED},
        [CB2_B] = {.led_index = 20, .color_channel = GREEN},
        [CB3_B] = {.led_index = 20, .color_channel = BLUE},
        // 2
        [CB1_C] = {.led_index = 21, .color_channel = RED},
        [CB2_C] = {.led_index = 21, .color_channel = GREEN},
        [CB3_C] = {.led_index = 21, .color_channel = BLUE},
        // 3
        [CB1_D] = {.led_index = 22, .color_channel = RED},
        [CB2_D] = {.led_index = 22, .color_channel = GREEN},
        [CB3_D] = {.led_index = 22, .color_channel = BLUE},
        // 4
        [CB1_E] = {.led_index = 23, .color_channel = RED},
        [CB2_E] = {.led_index = 23, .color_channel = GREEN},
        [CB3_E] = {.led_index = 23, .color_channel = BLUE},
        // 5
        [CB1_F] = {.led_index = 24, .color_channel = RED},
        [CB2_F] = {.led_index = 24, .color_channel = GREEN},
        [CB3_F] = {.led_index = 24, .color_channel = BLUE},
        // 6
        [CB1_G] = {.led_index = 25, .color_channel = RED},
        [CB2_G] = {.led_index = 25, .color_channel = GREEN},
        [CB3_G] = {.led_index = 25, .color_channel = BLUE},
        // 7
        [CB1_H] = {.led_index = 26, .color_channel = RED},
        [CB2_H] = {.led_index = 26, .color_channel = GREEN},
        [CB3_H] = {.led_index = 26, .color_channel = BLUE},
        // 8
        [CB1_I] = {.led_index = 27, .color_channel = RED},
        [CB2_I] = {.led_index = 27, .color_channel = GREEN},
        [CB3_I] = {.led_index = 27, .color_channel = BLUE},
        // 9
        [CB1_M] = {.led_index = 28, .color_channel = RED},
        [CB2_M] = {.led_index = 28, .color_channel = GREEN},
        [CB3_M] = {.led_index = 28, .color_channel = BLUE},
        // 0
        [CB1_N] = {.led_index = 29, .color_channel = RED},
        [CB2_N] = {.led_index = 29, .color_channel = GREEN},
        [CB3_N] = {.led_index = 29, .color_channel = BLUE},
        // -
        [CB1_O] = {.led_index = 30, .color_channel = RED},
        [CB2_O] = {.led_index = 30, .color_channel = GREEN},
        [CB3_O] = {.led_index = 30, .color_channel = BLUE},
        // =
        [CB1_P] = {.led_index = 31, .color_channel = RED},
        [CB2_P] = {.led_index = 31, .color_channel = GREEN},
        [CB3_P] = {.led_index = 31, .color_channel = BLUE},

        // left side - row 2
        [CB4_L] = {.led_index = 41, .color_channel = RED},
        [CB5_L] = {.led_index = 41, .color_channel = BLUE},
        [CB6_L] = {.led_index = 41, .color_channel = GREEN},

        // Tab
        [CA7_A] = {.led_index = 42, .color_channel = RED},
        [CA8_A] = {.led_index = 42, .color_channel = GREEN},
        [CA9_A] = {.led_index = 42, .color_channel = BLUE},
        // Q
        [CA7_B] = {.led_index = 43, .color_channel = RED},
        [CA8_B] = {.led_index = 43, .color_channel = GREEN},
        [CA9_B] = {.led_index = 43, .color_channel = BLUE},
        // W
        [CA7_C] = {.led_index = 44, .color_channel = RED},
        [CA8_C] = {.led_index = 44, .color_channel = GREEN},
        [CA9_C] = {.led_index = 44, .color_channel = BLUE},
        // E
        [CA7_D] = {.led_index = 45, .color_channel = RED},
        [CA8_D] = {.led_index = 45, .color_channel = GREEN},
        [CA9_D] = {.led_index = 45, .color_channel = BLUE},
        // R
        [CA7_E] = {.led_index = 46, .color_channel = RED},
        [CA8_E] = {.led_index = 46, .color_channel = GREEN},
        [CA9_E] = {.led_index = 46, .color_channel = BLUE},
        // T
        [CA7_F] = {.led_index = 47, .color_channel = RED},
        [CA8_F] = {.led_index = 47, .color_channel = GREEN},
        [CA9_F] = {.led_index = 47, .color_channel = BLUE},
        // Y
        [CA7_J] = {.led_index = 48, .color_channel = RED},
        [CA8_J] = {.led_index = 48, .color_channel = GREEN},
        [CA9_J] = {.led_index = 48, .color_channel = BLUE},
        // U
        [CA7_K] = {.led_index = 49, .color_channel = RED},
        [CA8_K] = {.led_index = 49, .color_channel = GREEN},
        [CA9_K] = {.led_index = 49, .color_channel = BLUE},
        // I
        [CA7_L] = {.led_index = 50, .color_channel = RED},
        [CA8_L] = {.led_index = 50, .color_channel = GREEN},
        [CA9_L] = {.led_index = 50, .color_channel = BLUE},
        // O
        [CA7_M] = {.led_index = 51, .color_channel = RED},
        [CA8_M] = {.led_index = 51, .color_channel = GREEN},
        [CA9_M] = {.led_index = 51, .color_channel = BLUE},
        // P
        [CA7_N] = {.led_index = 52, .color_channel = RED},
        [CA8_N] = {.led_index = 52, .color_channel = GREEN},
        [CA9_N] = {.led_index = 52, .color_channel = BLUE},
        // [
        [CA7_O] = {.led_index = 53, .color_channel = RED},
        [CA8_O] = {.led_index = 53, .color_channel = GREEN},
        [CA9_O] = {.led_index = 53, .color_channel = BLUE},
        // ]
        [CA7_P] = {.led_index = 54, .color_channel = RED},
        [CA8_P] = {.led_index = 54, .color_channel = GREEN},
        [CA9_P] = {.led_index = 54, .color_channel = BLUE},

        // left side - row 3
        [CB4_O] = {.led_index = 64, .color_channel = RED},
        [CB5_O] = {.led_index = 64, .color_channel = BLUE},
        [CB6_O] = {.led_index = 64, .color_channel = GREEN},

        // Caps Lock
        [CA4_A] = {.led_index = 65, .color_channel = RED},
        [CA5_A] = {.led_index = 65, .color_channel = GREEN},
        [CA6_A] = {.led_index = 65, .color_channel = BLUE},
        // A
        [CA4_B] = {.led_index = 66, .color_channel = RED},
        [CA5_B] = {.led_index = 66, .color_channel = GREEN},
        [CA6_B] = {.led_index = 66, .color_channel = BLUE},
        // S
        [CA4_C] = {.led_index = 67, .color_channel = RED},
        [CA5_C] = {.led_index = 67, .color_channel = GREEN},
        [CA6_C] = {.led_index = 67, .color_channel = BLUE},
        // D
        [CA4_G] = {.led_index = 68, .color_channel = RED},
        [CA5_G] = {.led_index = 68, .color_channel = GREEN},
        [CA6_G] = {.led_index = 68, .color_channel = BLUE},
        // F
        [CA4_H] = {.led_index = 69, .color_channel = RED},
        [CA5_H] = {.led_index = 69, .color_channel = GREEN},
        [CA6_H] = {.led_index = 69, .color_channel = BLUE},
        // G
        [CA4_I] = {.led_index = 70, .color_channel = RED},
        [CA5_I] = {.led_index = 70, .color_channel = GREEN},
        [CA6_I] = {.led_index = 70, .color_channel = BLUE},
        // H
        [CA4_J] = {.led_index = 71, .color_channel = RED},
        [CA5_J] = {.led_index = 71, .color_channel = GREEN},
        [CA6_J] = {.led_index = 71, .color_channel = BLUE},
        // J
        [CA4_K] = {.led_index = 72, .color_channel = RED},
        [CA5_K] = {.led_index = 72, .color_channel = GREEN},
        [CA6_K] = {.led_index = 72, .color_channel = BLUE},
        // K
        [CA4_L] = {.led_index = 73, .color_channel = RED},
        [CA5_L] = {.led_index = 73, .color_channel = GREEN},
        [CA6_L] = {.led_index = 73, .color_channel = BLUE},
        // L
        [CA4_M] = {.led_index = 74, .color_channel = RED},
        [CA5_M] = {.led_index = 74, .color_channel = GREEN},
        [CA6_M] = {.led_index = 74, .color_channel = BLUE},
        // ;
        [CA4_N] = {.led_index = 75, .color_channel = RED},
        [CA5_N] = {.led_index = 75, .color_channel = GREEN},
        [CA6_N] = {.led_index = 75, .color_channel = BLUE},
        // '
        [CA4_O] = {.led_index = 76, .color_channel = RED},
        [CA5_O] = {.led_index = 76, .color_channel = GREEN},
        [CA6_O] = {.led_index = 76, .color_channel = BLUE},
        // Return
        [CA4_P] = {.led_index = 77, .color_channel = RED},
        [CA5_P] = {.led_index = 77, .color_channel = GREEN},
        [CA6_P] = {.led_index = 77, .color_channel = BLUE},

        // left side - row 4
        [CB4_P] = {.led_index = 82, .color_channel = RED},
        [CB5_P] = {.led_index = 82, .color_channel = BLUE},
        [CB6_P] = {.led_index = 82, .color_channel = GREEN},

        // Left Shift
        [CA1_D] = {.led_index = 83, .color_channel = RED},
        [CA2_D] = {.led_index = 83, .color_channel = GREEN},
        [CA3_D] = {.led_index = 83, .color_channel = BLUE},
        // Z
        [CA1_F] = {.led_index = 84, .color_channel = RED},
        [CA2_F] = {.led_index = 84, .color_channel = GREEN},
        [CA3_F] = {.led_index = 84, .color_channel = BLUE},
        // X
        [CA1_G] = {.led_index = 85, .color_channel = RED},
        [CA2_G] = {.led_index = 85, .color_channel = GREEN},
        [CA3_G] = {.led_index = 85, .color_channel = BLUE},
        // C
        [CA1_H] = {.led_index = 86, .color_channel = RED},
        [CA2_H] = {.led_index = 86, .color_channel = GREEN},
        [CA3_H] = {.led_index = 86, .color_channel = BLUE},
        // V
        [CA1_I] = {.led_index = 87, .color_channel = RED},
        [CA2_I] = {.led_index = 87, .color_channel = GREEN},
        [CA3_I] = {.led_index = 87, .color_channel = BLUE},
        // B
        [CA1_J] = {.led_index = 88, .color_channel = RED},
        [CA2_J] = {.led_index = 88, .color_channel = GREEN},
        [CA3_J] = {.led_index = 88, .color_channel = BLUE},
        // N
        [CA1_K] = {.led_index = 89, .color_channel = RED},
        [CA2_K] = {.led_index = 89, .color_channel = GREEN},
        [CA3_K] = {.led_index = 89, .color_channel = BLUE},
        // M
        [CA1_L] = {.led_index = 90, .color_channel = RED},
        [CA2_L] = {.led_index = 90, .color_channel = GREEN},
        [CA3_L] = {.led_index = 90, .color_channel = BLUE},
        // ,
        [CA1_M] = {.led_index = 91, .color_channel = RED},
        [CA2_M] = {.led_index = 91, .color_channel = GREEN},
        [CA3_M] = {.led_index = 91, .color_channel = BLUE},
        // .
        [CA1_N] = {.led_index = 92, .color_channel = RED},
        [CA2_N] = {.led_index = 92, .color_channel = GREEN},
        [CA3_N] = {.led_index = 92, .color_channel = BLUE},
        // /
        [CA1_O] = {.led_index = 93, .color_channel = RED},
        [CA2_O] = {.led_index = 93, .color_channel = GREEN},
        [CA3_O] = {.led_index = 93, .color_channel = BLUE},
        // Right Shift
        [CA1_P] = {.led_index = 94, .color_channel = RED},
        [CA2_P] = {.led_index = 94, .color_channel = GREEN},
        [CA3_P] = {.led_index = 94, .color_channel = BLUE},

        // left side - row 6
        [CA1_C] = {.led_index = 116, .color_channel = RED},
        [CA2_C] = {.led_index = 116, .color_channel = BLUE},
        [CA3_C] = {.led_index = 116, .color_channel = GREEN},
    },
};
#endif  // RGB_MATRIX_ENABLE
