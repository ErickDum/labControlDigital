#include <Arduino.h>
#include <buttons_control.h>

void init_button(BUTTON* button) {
    pinMode(button->pin, button->pull_up ? INPUT_PULLUP : INPUT);
    button->state = BUTTON_DOWN;
}