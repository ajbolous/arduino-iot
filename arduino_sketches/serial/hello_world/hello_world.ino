#include <Arduino.h>

void setup() { Serial.begin(115200); }

// Periodically prints Hello world !
void loop() {
  Serial.println("Hello World !");
  delay(1000);
}
