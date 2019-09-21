// FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

void InitWiFi(const String &ssid, const String &password)
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
        delay(300);
    Serial.println("Connected with IP: " + WiFi.localIP().toString());
}

void InitFireBase(const String &host, const String &auth_key)
{
    Firebase.begin(host, auth_key);
    Firebase.reconnectWiFi(true);
}

void setup()
{
    Serial.begin(115200);
    InitWiFi("AbuJaberHome", "59405940");
    InitFireBase("arduino-iot-2019.firebaseio.com",
                 "ptnN6qEkNdazs22bc1F31G0jFSW3JrOHUgZIxfvq");
    pinMode(LED_BUILTIN, OUTPUT);
}

FirebaseData firebaseData;

void loop()
{
    if (Firebase.getInt(firebaseData, "/room/lamp_status"))
    {
        if (firebaseData.intData() == 1)
        {
            digitalWrite(LED_BUILTIN, LOW);
        }
        else
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
    }

    delay(1000);
}
