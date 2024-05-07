#include <Arduino.h>

typedef const uint16_t LED;

// Define the pins for the LEDs
LED LED_B = 2;
LED LED_R = 3;
LED LED_Y = 4;
LED LED_G = 5;

// Define the sequence of LEDs
LED led_sequence[] = {LED_B, LED_R, LED_Y, LED_G};

LED last_LED = sizeof(led_sequence) / sizeof(led_sequence[0]) - 1;

// Function prototypes
bool blink_led(LED led, uint16_t delay_time);
void activate_sequence(LED *);

void setup() {
  for (LED led : led_sequence) {
    pinMode(led, OUTPUT);
  }
}

void loop() {
  activate_sequence(led_sequence);
}

// Function definitions
void activate_sequence(LED *led_sequence) {
  for(uint16_t i = 0; i <= last_LED; i++) {
    blink_led(led_sequence[i], 1000);
  }
}

bool blink_led(LED led, uint16_t delay_time) {
  if (delay_time <= 0) return false;

  digitalWrite(led, HIGH);
  delay(delay_time);
  digitalWrite(led, LOW);

  return true;
}