// FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include "sensor_node.h"
#include <ESP8266WiFi.h>

void InitWiFi(const String &ssid, const String &password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    delay(300);
  Serial.println("Connected with IP: " + WiFi.localIP().toString());
}

#include "FirebaseESP8266.h"


void InitFireBase(const String &host, const String &auth_key) {
  Firebase.begin(host, auth_key);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  InitWiFi("AbuJaberHome", "59405940");
  InitFireBase("arduino-iot-2019.firebaseio.com",
               "ptnN6qEkNdazs22bc1F31G0jFSW3JrOHUgZIxfvq");
}

Node node("home-office", 12);

void loop() {
  node.SendData();
  delay(60000);
}
