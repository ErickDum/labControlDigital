#include <Arduino.h>
#include <buttons_control.h>
#include <utils.h>

DelayState buttons_delay_state = {.first_count = true};

void fsm_button_update(BUTTON* button);
void fsm_button_error(BUTTON* button);

void init_button(BUTTON* button) {
    pinMode(button->pin, INPUT);
    button->state = BUTTON_UP;
}

void fsm_right_direction_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control) {
    fsm_button_update(button);
    if (button->state == BUTTON_DOWN) {
        sequence_control->direction = true;
    }
}

void fsm_left_direction_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control) {
    fsm_button_update(button);
    if (button->state == BUTTON_DOWN) {
        sequence_control->direction = false;
    }
}

void fsm_increase_delay_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control) {
    fsm_button_update(button);
    if (button->state == BUTTON_DOWN) {
        sequence_control->delay_position = (sequence_control->delay_position + 1);
        if (sequence_control->delay_position >= sequence_control->delay_values_size) {
            sequence_control->delay_position --;
        }
    }
}

void fsm_decrease_delay_button_update(BUTTON* button, SEQUENCE_CONTROL* sequence_control) {
    fsm_button_update(button);
    if (button->state == BUTTON_DOWN) {
        sequence_control->delay_position = (sequence_control->delay_position - 1);
        if (sequence_control->delay_position < 0) {
            sequence_control->delay_position ++;
        }
    }
}


// FSM for the buttons
void fsm_button_update(BUTTON* button) {
    switch (button->state) {
        case BUTTON_UP:
            if (digitalRead(button->pin) == button->pull_down) {
                button->state = BUTTON_FALLING;
            }
            break;
        case BUTTON_DOWN:
            if (digitalRead(button->pin) != button->pull_down) {
                button->state = BUTTON_RISING;
            }
            break;
        case BUTTON_FALLING:
            if(nb_delay(&buttons_delay_state, 40)) {
                if (digitalRead(button->pin) == button->pull_down) {
                    button->state = BUTTON_DOWN;
                } else {
                    button->state = BUTTON_UP;
                }
            }
            break;
        case BUTTON_RISING:
            if(nb_delay(&buttons_delay_state, 40)) {
                if (digitalRead(button->pin) == button->pull_down) {
                    button->state = BUTTON_DOWN;
                } else {
                    button->state = BUTTON_UP;
                }
            }
            break;
        default:
            fsm_button_error(button);
            break;
    }
}

void fsm_button_error(BUTTON* button) {
    button->state = BUTTON_UP;
}