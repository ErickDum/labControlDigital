#include <Arduino.h>
#include <leds_control.h>
#include <buttons_control.h>
#include <utils.h>

// Define properties for the LEDs
LED LED_BLUE = {.pin = 2, 
                .color = "blue"};
LED LED_RED = {.pin = 3,
               .color = "red"};
LED LED_YELLOW = {.pin = 4,
                  .color = "yellow"};
LED LED_GREEN = {.pin = 5,
                 .color = "green"};

// Define buttons to change the direction of the sequence
BUTTON right_direction_button = {.pin = 6, 
                                 .pull_up = true};
BUTTON left_direction_button = {.pin = 7, 
                                .pull_up = true};

// Define buttons to increase and decrease the delay
BUTTON increase_delay_button = {.pin = 8, 
                                .pull_up = true};
BUTTON decrease_delay_button = {.pin = 9, 
                                .pull_up = true};

// Define the delay values
uint16_t delay_values[] = {1000, 500, 250, 100};

// Define the sequence of LEDs
LED led_sequence[] = {LED_BLUE, LED_RED, LED_YELLOW, LED_GREEN};

SECUENCE_CONTROL sequence_control;

void setup() {
  Serial.begin(9600);

  // Initialize the LEDs
  for (uint8_t i = 0; i < sizeof(led_sequence) / sizeof(led_sequence[0]); i++) {
      init_led(&led_sequence[i]);
  }

  // Initialize the buttons
  init_button(&right_direction_button);
  init_button(&left_direction_button);
  init_button(&increase_delay_button);
  init_button(&decrease_delay_button);
  
  init_secuence_control(&sequence_control, led_sequence, sizeof(led_sequence) / sizeof(led_sequence[0]), 
                        delay_values, sizeof(delay_values) / sizeof(delay_values[0]));
}

void loop() {
  update_sequence(&sequence_control);
}