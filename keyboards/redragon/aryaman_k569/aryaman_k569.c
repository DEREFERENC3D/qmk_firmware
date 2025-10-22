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
const sled1734x_led_t PROGMEM g_sled1734x_leds[RGB_MATRIX_LED_COUNT] = {
    // driver index, red pin, green pin, blue pin
    // color order is RBG
    {1, CA7_I, CA8_I, CA9_I}, // side - left row 0

    {1, CB4_A, CB6_A, CB5_A}, // ESC

    {1, CB4_B, CB6_B, CB5_B}, // F1
    {1, CB4_C, CB6_C, CB5_C}, // F2
    {1, CB4_D, CB6_D, CB5_D}, // F3
    {1, CB4_E, CB6_E, CB5_E}, // F4

    {1, CB4_F, CB6_F, CB5_F}, // F5
    {1, CB4_G, CB6_G, CB5_G}, // F6
    {1, CB4_H, CB6_H, CB5_H}, // F7
    {1, CB4_I, CB6_I, CB5_I}, // F8

    {1, CB4_J, CB6_J, CB5_J}, // F9
    {1, CB4_K, CB6_K, CB5_K}, // F10
    {0, CB4_A, CB6_A, CB5_A}, // F11
    {0, CB4_B, CB6_B, CB5_B}, // F12

    {0, CB4_C, CB6_C, CB5_C}, // Print Screen
    {0, CB4_D, CB6_D, CB5_D}, // Scroll Lock
    {0, CB4_E, CB6_E, CB5_E}, // Pause Break

    {0, CB1_L, CB2_L, CB3_L}, // side - right row 0

    {1, CB1_L, CB2_L, CB3_L}, // side - left row 1

    {1, CB1_A, CB3_A, CB2_A}, // ` (grave / tilde)
    {1, CB1_B, CB3_B, CB2_B}, // 1
    {1, CB1_C, CB3_C, CB2_C}, // 2
    {1, CB1_D, CB3_D, CB2_D}, // 3
    {1, CB1_E, CB3_E, CB2_E}, // 4
    {1, CB1_F, CB3_F, CB2_F}, // 5
    {1, CB1_G, CB3_G, CB2_G}, // 6
    {1, CB1_H, CB3_H, CB2_H}, // 7
    {1, CB1_I, CB3_I, CB2_I}, // 8
    {1, CB1_M, CB3_M, CB2_M}, // 9
    {1, CB1_N, CB3_N, CB2_N}, // 0
    {1, CB1_O, CB3_O, CB2_O}, // -
    {1, CB1_P, CB3_P, CB2_P}, // =
    {0, CB4_K, CB6_K, CB5_K}, // Backspace

    {0, CB1_A, CB3_A, CB2_A}, // Insert
    {0, CB1_B, CB3_B, CB2_B}, // Home
    {0, CB1_C, CB3_C, CB2_C}, // Page Up

    {0, CB1_D, CB3_D, CB2_D}, // Num Lock
    {0, CB1_E, CB3_E, CB2_E}, // Num /
    {0, CB1_F, CB3_F, CB2_F}, // Num *
    {0, CB1_G, CB3_G, CB2_G}, // Num -

    {0, CB1_M, CB2_M, CB3_M}, // side - right row 1

    {1, CB4_L, CB5_L, CB6_L}, // side - left row 2

    {1, CA7_A, CA9_A, CA8_A}, // Tab
    {1, CA7_B, CA9_B, CA8_B}, // Q
    {1, CA7_C, CA9_C, CA8_C}, // W
    {1, CA7_D, CA9_D, CA8_D}, // E
    {1, CA7_E, CA9_E, CA8_E}, // R
    {1, CA7_F, CA9_F, CA8_F}, // T
    {1, CA7_J, CA9_J, CA8_J}, // Y
    {1, CA7_K, CA9_K, CA8_K}, // U
    {1, CA7_L, CA9_L, CA8_L}, // I
    {1, CA7_M, CA9_M, CA8_M}, // O
    {1, CA7_N, CA9_N, CA8_N}, // P
    {1, CA7_O, CA9_O, CA8_O}, // [
    {1, CA7_P, CA9_P, CA8_P}, // ]
    {0, CB1_H, CB3_H, CB2_H}, // Backslash

    {0, CB1_I, CB3_I, CB2_I}, // Del
    {0, CA7_A, CA9_A, CA8_A}, // End
    {0, CA7_B, CA9_B, CA8_B}, // Page Down

    {0, CA7_C, CA9_C, CA8_C}, // Num 7
    {0, CA7_D, CA9_D, CA8_D}, // Num 8
    {0, CA7_E, CA9_E, CA8_E}, // Num 9
    {0, CA7_F, CA9_F, CA8_F}, // Num +

    {0, CB1_N, CB2_N, CB3_N}, // side - right row 2

    {1, CB4_O, CB5_O, CB6_O}, // side - left row 3

    {1, CA4_A, CA6_A, CA5_A}, // Caps Lock
    {1, CA4_B, CA6_B, CA5_B}, // A
    {1, CA4_C, CA6_C, CA5_C}, // S
    {1, CA4_G, CA6_G, CA5_G}, // D
    {1, CA4_H, CA6_H, CA5_H}, // F
    {1, CA4_I, CA6_I, CA5_I}, // G
    {1, CA4_J, CA6_J, CA5_J}, // H
    {1, CA4_K, CA6_K, CA5_K}, // J
    {1, CA4_L, CA6_L, CA5_L}, // K
    {1, CA4_M, CA6_M, CA5_M}, // L
    {1, CA4_N, CA6_N, CA5_N}, // ;
    {1, CA4_O, CA6_O, CA5_O}, // '
    {1, CA4_P, CA6_P, CA5_P}, // Return

    {0, CA4_A, CA6_A, CA5_A}, // Num 4
    {0, CA4_B, CA6_B, CA5_B}, // Num 5
    {0, CA4_C, CA6_C, CA5_C}, // Num 6

    {0, CB1_O, CB2_O, CB3_O}, // side - right row 3

    {1, CB4_P, CB5_P, CB6_P}, // side - left row 4

    {1, CA1_D, CA3_D, CA2_D}, // Left Shift
    {1, CA1_F, CA3_F, CA2_F}, // Z
    {1, CA1_G, CA3_G, CA2_G}, // X
    {1, CA1_H, CA3_H, CA2_H}, // C
    {1, CA1_I, CA3_I, CA2_I}, // V
    {1, CA1_J, CA3_J, CA2_J}, // B
    {1, CA1_K, CA3_K, CA2_K}, // N
    {1, CA1_L, CA3_L, CA2_L}, // M
    {1, CA1_M, CA3_M, CA2_M}, // ,
    {1, CA1_N, CA3_N, CA2_N}, // .
    {1, CA1_O, CA3_O, CA2_O}, // /
    {1, CA1_P, CA3_P, CA2_P}, // Right Shift

    {0, CA4_G, CA6_G, CA5_G}, // Arrow Up

    {0, CA4_H, CA6_H, CA5_H}, // Num 1
    {0, CA4_I, CA6_I, CA5_I}, // Num 2
    {0, CA4_J, CA6_J, CA5_J}, // Num 3
    {0, CA4_K, CA6_K, CA5_K}, // Num Enter

    {0, CB1_P, CB2_P, CB3_P}, // side - right row 4

    {1, CA4_F, CA5_F, CA6_F}, // side - left row 5

    {0, CA1_D, CA3_D, CA2_D}, // Ctrl
    {0, CA1_E, CA3_E, CA2_E}, // Win
    {0, CA1_F, CA3_F, CA2_F}, // Left Alt
    {0, CA1_H, CA3_H, CA2_H}, // Space
    {0, CA1_J, CA3_J, CA2_J}, // Right Alt
    {0, CA1_K, CA3_K, CA2_K}, // Fn
    {0, CA1_L, CA3_L, CA2_L}, // Right Menu
    {0, CA1_N, CA3_N, CA2_N}, // Right Ctrl

    {0, CA1_O, CA3_O, CA2_O}, // Arrow Left
    {0, CA1_P, CA3_P, CA2_P}, // Arrow Down
    {0, CA4_L, CA6_L, CA5_L}, // Arrow Right

    {0, CA4_M, CA6_M, CA5_M}, // Num 0
    {0, CA4_N, CA6_N, CA5_N}, // Num .

    {0, CA4_O, CA5_O, CA6_O}, // side - right row 5

    {1, CA1_C, CA2_C, CA3_C}, // side - left row 6

    {0, CA4_P, CA5_P, CA6_P}, // side - right row 6
};
#endif  // RGB_MATRIX_ENABLE
