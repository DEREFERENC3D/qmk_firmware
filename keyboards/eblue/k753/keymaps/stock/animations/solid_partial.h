#ifdef ENABLE_LED_MATRIX_CUSTOM_SOLID_PARTIAL
LED_MATRIX_EFFECT(SOLID_PARTIAL)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS
#   include "../led_matrix_custom.h"
#   include "../keymap.h"
extern user_config_t user_config;
extern bool edit_mode;
extern uint8_t custom_buf[CUSTOM_MODE_SIZE];

const static PROGMEM uint8_t NO_MODE_LEDS[] = {NO_LED};

const static uint8_t MODE_1_LEDS[] = {
    0,

    39,

    59,
    60,
    61,

    86,

    99,
    100,
    101,

    NO_LED
};
const static uint8_t MODE_2_LEDS[] = {
    17,
    18,
    19,
    20,
    21,
    31,
    32,

    38,
    39,
    40,
    41,
    52,
    53,

    59,
    60,
    61,
    63,

    74,
    79,

    91,
    93,
    94,

    NO_LED
};
const static uint8_t MODE_3_LEDS[] = {
    17,
    18,
    19,
    20,
    21,
    22,
    23,

    38,
    39,
    40,
    41,
    42,

    59,
    60,
    61,
    62,
    63,

    74,
    77,
    78,

    91,

    NO_LED
};
const static uint8_t MODE_4_LEDS[] = {
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,

    38,
    39,
    40,
    41,
    42,
    43,
    44,
    47,

    59,
    60,
    61,
    62,
    63,
    64,
    66,
    67,

    74,
    75,
    76,
    80,
    81,

    91,
    93,
    94,

    NO_LED
};
const static uint8_t MODE_5_LEDS[] = {
    0,

    16,
    17,
    18,
    19,
    20,
    21,
    22,

    37,
    38,
    39,
    40,
    41,

    61,
    62,
    63,

    78,
    79,

    91,
    93,
    94,

    NO_LED
};
const static uint8_t MODE_6_LEDS[] = {
    39,
    41,

    59,
    60,
    61,
    
    74,
    86,

    91,
    93,
    99,
    100,
    101,

    NO_LED
};
const static uint8_t MODE_7_LEDS[] = {
    17,
    18,
    19,
    20,

    39,
    40,
    41,

    59,
    60,
    62,

    74,
    75,
    76,
    77,
    78,
    86,

    91,
    93,
    94,
    99,
    100,
    101,

    NO_LED
};
const static uint8_t MODE_8_LEDS[] = {
    17,
    18,
    19,
    20,
    21,
    22,

    38,
    39,
    40,
    41,

    61,
    62,

    79,

    NO_LED
};

bool SOLID_PARTIAL(effect_params_t* params) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    const uint8_t *mode_leds;
    switch (user_config.custom_mode) {
        case MODE_1:
            mode_leds = MODE_1_LEDS;
            break;
        case MODE_2:
            mode_leds = MODE_2_LEDS;
            break;
        case MODE_3:
            mode_leds = MODE_3_LEDS;
            break;
        case MODE_4:
            mode_leds = MODE_4_LEDS;
            break;
        case MODE_5:
            mode_leds = MODE_5_LEDS;
            break;
        case MODE_6:
            mode_leds = MODE_6_LEDS;
            break;
        case MODE_7:
            mode_leds = MODE_7_LEDS;
            break;
        case MODE_8:
            mode_leds = MODE_8_LEDS;
            break;
        case MODE_9:
        case MODE_0:
            mode_leds = edit_mode ? custom_buf : user_config.custom_mode_data[user_config.custom_mode - CUSTOM_MODE_START];
            break;
        default:
            mode_leds = NO_MODE_LEDS;
            break;
    }

    uint8_t brightness = led_matrix_get_val();

    if (user_config.custom_mode < CUSTOM_MODE_START || mode_leds == NO_MODE_LEDS) {
        led_matrix_set_value_all(0);
        uint8_t next_on = pgm_read_byte(&mode_leds[0]);
        for (int i = 1; next_on != NO_LED; i++) {
            led_matrix_set_value(next_on, brightness);
            next_on = pgm_read_byte(&mode_leds[i]);
        }
    } else {
        for (uint8_t i = led_min; i < led_max; i++) {
            LED_MATRIX_TEST_LED_FLAGS();
    
            bool on = custom_mode_get(mode_leds, i);
            led_matrix_set_value(i, on ? brightness : 0);
        }
    }

    return led_matrix_check_finished_leds(led_max);
}
#    endif // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_LED_MATRIX_CUSTOM_SOLID_PARTIAL
