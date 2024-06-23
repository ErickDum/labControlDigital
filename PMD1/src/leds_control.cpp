#include <Arduino.h>
#include <leds_control.h>
#include <utils.h>

DelayState leds_delay_state = {.first_count = true};

void init_led(LED* led) {
    pinMode(led->pin, OUTPUT);
    led->state = false;
}

void init_sequence_control(SEQUENCE_CONTROL* sequence_control, LED* led_sequence, uint8_t led_sequence_size, uint16_t* delay_values, uint8_t delay_values_size) {
    sequence_control->direction = true;
    sequence_control->delay_position = 0;
    sequence_control->led_sequence = led_sequence;
    sequence_control->led_sequence_size = led_sequence_size;
    sequence_control->delay_values = delay_values;
    sequence_control->delay_values_size = delay_values_size;
}

void update_sequence(SEQUENCE_CONTROL* sequence_control){
    static int16_t current_led = 0;
    static bool led_state = false;

    if (!led_state and nb_delay(&leds_delay_state ,sequence_control->delay_values[sequence_control->delay_position])) {
        digitalWrite(sequence_control->led_sequence[current_led].pin, HIGH);
        led_state = true;
    } else if(led_state and nb_delay(&leds_delay_state ,sequence_control->delay_values[sequence_control->delay_position])) {
        digitalWrite(sequence_control->led_sequence[current_led].pin, LOW);
        led_state = false;
        current_led = current_led + (sequence_control->direction ? 1 : -1);
        if (current_led == sequence_control->led_sequence_size) {
            current_led = 0;
        } else if (current_led < 0) {
            current_led = sequence_control->led_sequence_size - 1;
        }
    }
}