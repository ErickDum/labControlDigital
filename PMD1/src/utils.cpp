#include <Arduino.h>
#include <utils.h>

bool nb_delay(DelayState* delay_state, uint16_t delay){
    // Check if it is the first time the function is called
    if (delay_state->first_count) {
        delay_state->initial_time = millis();
        delay_state->first_count = false;
    }

    uint16_t current_time = millis();

    // Check if the delay has passed
    if (current_time - delay_state->initial_time > delay) {
        delay_state->initial_time = current_time;
        delay_state->first_count = true;
        return true;
    } else {
        return false;
    }
}