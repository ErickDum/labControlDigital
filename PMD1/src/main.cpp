#include <Arduino.h>
#include <stdint.h>

uint16_t leds[4] = {2, 3, 4, 5};

void turn_on_led(uint16_t led);
void turn_off_led(uint16_t led);

void setup() {
  for (uint16_t led: leds){
    pinMode(led, OUTPUT);
  }
}

void loop() {
  for (uint16_t led: leds){
    turn_on_led(led);
    delay(1000);
    turn_off_led(led);
    delay(1000);
  }
}

void turn_on_led(uint16_t led){
  digitalWrite(led, HIGH);
}

void turn_off_led(uint16_t led){
  digitalWrite(led, LOW);
}