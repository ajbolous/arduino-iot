#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char val = Serial.read();
    digitalWrite(LED_BUILTIN, val == '1' ? LOW : HIGH);
  }
  delay(50);
}
