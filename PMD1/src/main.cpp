#include <Arduino.h>

typedef const int16_t LED;

// Define the pins for the LEDs
LED LED_B = 2;
LED LED_R = 3;
LED LED_Y = 4;
LED LED_G = 5;

bool reverse = false;

// Define the sequence of LEDs
LED led_sequence[] = {LED_B, LED_R, LED_Y, LED_G};

LED last_LED = sizeof(led_sequence) / sizeof(led_sequence[0]) - 1;

// Function prototypes
bool read_key(uint16_t key);
void secuence(LED *, bool reverse);
uint16_t nb_delay(uint16_t delay);

// Setup function
void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  for (LED led : led_sequence) {
    pinMode(led, OUTPUT);
  }
}

// Loop function
void loop() {
  if (read_key(6)) reverse = !reverse;
  Serial.println((reverse) ? "Reverse" : "Normal");
  secuence(led_sequence, reverse);
}

// Function definitions
bool read_key(uint16_t key){
  uint16_t key_value = digitalRead(key);
  return key_value == 1 ? false : true;
}

void secuence(LED *led_sequence, bool reverse){
  static int16_t current_LED = 0;
  static bool state = false;
  static uint16_t delay = 750;
  int16_t next_step = (reverse) ? -1 : 1;

  if (!state and nb_delay(delay)){
    digitalWrite(led_sequence[current_LED], HIGH);
    state = true;
  } else if (state and nb_delay(delay)){
    digitalWrite(led_sequence[current_LED], LOW);
    state = false;
    current_LED += next_step;
  }

  if (current_LED > last_LED) {
    current_LED = 0;
  }

  if (current_LED < 0) {
    current_LED = last_LED;
  }
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