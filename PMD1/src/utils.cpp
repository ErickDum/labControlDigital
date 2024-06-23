#include <Arduino.h>
#include <utils.h>

bool nb_delay(DelayState* delay_state, uint16_t delay){
    if (delay_state->first_count) {
        delay_state->initial_time = millis();
        delay_state->first_count = false;
    }

    uint16_t current_time = millis();

    if (current_time - delay_state->initial_time > delay) {
        delay_state->initial_time = current_time;
        delay_state->first_count = true;
        return true;
    } else {
        return false;
    }
}