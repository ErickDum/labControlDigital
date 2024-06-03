#include <Arduino.h>

typedef const int16_t LED;
uint16_t nb_delay(uint16_t delay);

// Function to read the key
bool read_key(uint16_t key){
  uint16_t key_value = digitalRead(key);
  return key_value == 1 ? true : false;
}

// Function to change the sequence of the LEDs
void secuence(LED led_sequence[], bool reverse, uint16_t delay, LED last_LED){
  static int16_t current_LED = 0;
  static bool state = false;
  int16_t next_step = (reverse) ? -1 : 1;

  if (!state and nb_delay(delay)){
    digitalWrite(led_sequence[current_LED], HIGH);
    state = true;
  } else if (state and nb_delay(delay)){
    digitalWrite(led_sequence[current_LED], LOW);
    state = false;
    current_LED += next_step;
  }

  // If the current LED is greater than the last LED, reset the current LED to 0
  if (current_LED > last_LED) current_LED = 0;
  if (current_LED < 0) current_LED = last_LED;
}


// Function to create a non-blocking delay
uint16_t nb_delay(uint16_t delay){
  // Static variables are initialized only once
  static bool first_time = true;
  static uint16_t initial_time = 0;

 // If it is the first time, initialize the initial time 
  if(first_time){
    initial_time = millis();
    first_time = false;
  }
  uint16_t current_time = millis();
  
  // If the difference between the current time and the initial time is greater than the delay, return 1
  if(current_time - initial_time > delay){
    initial_time = current_time;
    first_time = true;
    return 1;
  } else {
    return 0;
  }
}