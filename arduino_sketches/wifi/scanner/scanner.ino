#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
}

void loop() {
  int n = WiFi.scanNetworks();
  Serial.println("\nNetworks found: " + n);
  // Print SSID and RSSI for each network found
  for (int i = 0; i < n; ++i) {
    Serial.println(WiFi.SSID(i) + " RSSI: " + WiFi.RSSI(i));
  }

  Serial.println("");
  delay(5000);
}
