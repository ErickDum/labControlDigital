#include <Arduino.h>
#include <utils.h>

bool nb_delay(uint16_t delay){
    static bool first_count = true;
    static uint16_t initial_time = 0;

    if (first_count) {
        initial_time = millis();
        first_count = false;
    }

    uint16_t current_time = millis();

    if (current_time - initial_time > delay) {
        initial_time = current_time;
        first_count = true;
        return true;
    } else {
        return false;
    }
}