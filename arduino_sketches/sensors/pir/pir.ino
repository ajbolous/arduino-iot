#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(12, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  // Read the value of the sensor, if > 0 -> motion is detected.
  if (digitalRead(12)) {
    Serial.println("Motion detected !!");
  }
  delay(500);
}
