#include <Arduino.h>
#include <DHTesp.h>

DHTesp dht;

void setup() {
 Serial.begin(115200);
 dht.setup(12, DHTesp::DHT22);
}

// the loop function runs over and over again forever
void loop() {
 //Read data and store it to variables hum and temp
 TempAndHumidity temp_humidity = dht.getTempAndHumidity();
 //Print temp and humidity values to serial monitor
 Serial.print(temp_humidity.temperature);
 Serial.print("\t");
 Serial.println(temp_humidity.humidity);
 delay(2000);
}
