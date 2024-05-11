#include <Arduino.h>
#include "module.h"
typedef const int16_t LED;


// Define the pins for the LEDs
LED LED_B = 2;
LED LED_R = 3;
LED LED_Y = 4;
LED LED_G = 5;

// Define the pins for the buttons
uint16_t right_direction_button = 6;
uint16_t left_direction_button = 7;

// Define the pins for the delay buttons
uint16_t first_delay_button = 8;
uint16_t second_delay_button = 9;

// Define the delay values
uint16_t first_delay = 750;
uint16_t second_delay = 200;

// Define the sequence of LEDs
LED led_sequence[] = {LED_B, LED_R, LED_Y, LED_G};

// Setup function
void setup() {
  pinMode(right_direction_button, INPUT);
  pinMode(left_direction_button, INPUT);
  for (LED led : led_sequence) {
    pinMode(led, OUTPUT);
  }
}

// Loop function
void loop() {
  static bool reverse = false;
  static uint16_t delay = first_delay;
  static LED last_LED = sizeof(led_sequence) / sizeof(led_sequence[0]) - 1;

  if (read_key(6)) reverse = false;
  if (read_key(7)) reverse = true;
  if (read_key(8)) delay = first_delay;
  if (read_key(9)) delay = second_delay;

  secuence(led_sequence, reverse, delay, last_LED);
  
}