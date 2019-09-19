#include <Arduino.h>

void setup() { Serial.begin(115200); }

// Echos back the bytes received.
void loop() {
  if (Serial.available()) {
    Serial.write(Serial.read());
  }
}
