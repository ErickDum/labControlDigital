# ifndef module_h
# define module_h

# include <Arduino.h>

typedef const int16_t LED;

bool read_key(uint16_t key);
void secuence(LED led_secuence[], bool reverse, uint16_t delay, LED last_LED);
uint16_t nb_delay(uint16_t delay);

# endif