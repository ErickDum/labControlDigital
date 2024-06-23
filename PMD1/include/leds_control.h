#ifndef LEDS_CONTROL_H
#define LEDS_CONTROL_H

typedef struct {
    uint16_t pin;
    String color;
    bool state; // true for on, false for off
} LED;

typedef struct{
    bool direction; // true for right, false for left
    uint16_t delay;
    LED* led_sequence;
    uint8_t led_sequence_size;
    uint16_t* delay_values;
    uint8_t delay_values_size;
} SECUENCE_CONTROL;


void init_led(LED* led);

void init_secuence_control(SECUENCE_CONTROL* sequence_control, LED* led_sequence, 
                           uint8_t led_sequence_size, uint16_t* delay_values, uint8_t delay_values_size);

void update_sequence(SECUENCE_CONTROL* sequence_control);

#endif