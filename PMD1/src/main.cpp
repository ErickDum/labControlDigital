#include <Arduino.h>

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

// Define the last LED
LED last_LED = sizeof(led_sequence) / sizeof(led_sequence[0]) - 1;

// Function prototypes
bool read_key(uint16_t key);
void secuence(LED *, bool reverse, uint16_t delay);
uint16_t nb_delay(uint16_t delay);

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

  if (read_key(6)) reverse = false;
  if (read_key(7)) reverse = true;
  if (read_key(8)) delay = first_delay;
  if (read_key(9)) delay = second_delay;

  secuence(led_sequence, reverse, delay);
}

// Function definitions
bool read_key(uint16_t key){
  uint16_t key_value = digitalRead(key);
  return key_value == 1 ? true : false;
}

void secuence(LED *led_sequence, bool reverse, uint16_t delay){
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