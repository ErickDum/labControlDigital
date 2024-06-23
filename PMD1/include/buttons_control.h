// led_control.h
#ifndef BUTTONS_CONTROL_H
#define BUTTONS_CONTROL_H

#include <Arduino.h>

typedef enum {
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_FALLING,
  BUTTON_RISING
} fsm_button_state;

typedef struct {
    uint16_t pin;
    bool pull_up; // true para pull up, false para pull down
    fsm_button_state state; // true para encendido, false para apagado
} BUTTON;

void init_button(BUTTON* button);
#endif