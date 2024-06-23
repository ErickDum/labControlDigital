#ifndef UTILS_H
#define UTILS_H

typedef struct {
    bool first_count;
    uint16_t initial_time;
} DelayState;

bool nb_delay(DelayState* delay_state, uint16_t delay);

#endif