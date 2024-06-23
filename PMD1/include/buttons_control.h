// led_control.h
#ifndef BUTTONS_CONTROL_H
#define BUTTONS_CONTROL_H

#include <leds_control.h>
typedef enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_FALLING,
  BUTTON_RISING
} fsm_button_state;

typedef struct {
    uint16_t pin;
    bool pull_down; // true para pull up, false para pull down
    fsm_button_state state; // true para encendido, false para apagado
} BUTTON;

void init_button(BUTTON* button);
void fsm_right_direction_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control);
void fsm_left_direction_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control);
void fsm_increase_delay_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control);
void fsm_decrease_delay_button_update(BUTTON* button,SEQUENCE_CONTROL* sequence_control);
#endif