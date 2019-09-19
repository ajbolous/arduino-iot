#include <Arduino.h>

void setup() {}

void loop() {
  // Increase the LED intensity from 0 - 1024.
  for (int val = 0; val <= 1024; val += 5) {
    analogWrite(LED_BUILTIN, val);
    delay(10);
  }
  // Decrease the LED intensity.
  for (int val = 1024; val >= 0; val -= 5) {
    analogWrite(LED_BUILTIN, val);
    delay(10);
  }
}
