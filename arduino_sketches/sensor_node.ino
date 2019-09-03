//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"

#include <ESP8266WiFi.h>
#include <DHTesp.h>

void InitWiFi(const String &ssid, const String &password)
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(300);
  Serial.println("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void InitFireBase(const String &host, const String &auth_key)
{
  Firebase.begin(host, auth_key);
  Firebase.reconnectWiFi(true);
}

class Node
{
public:
  Node(const String &name, int dht_pin) : name_(name), node_path_("/nodes/" + name), data_path_("/data/" + name)
  {
    dht_.setup(dht_pin, DHTesp::DHT22);
  }

  bool SendData()
  {
    if (!Firebase.setTimestamp(data_obj_, node_path_))
      Serial.println("Unable to register with firebase");

    TempAndHumidity temp_and_hum = dht_.getTempAndHumidity();
    json_obj_.clear()
        .addDouble("temperature", temp_and_hum.temperature)
        .addDouble("humidity", temp_and_hum.humidity);

    if (!Firebase.pushJSON(data_obj_, data_path_, json_obj_))
      Serial.println("Failed: " + data_obj_.errorReason());
  }

private:
  String name_;
  String node_path_;
  String data_path_;
  FirebaseData data_obj_;
  FirebaseJson json_obj_;
  DHTesp dht_;
};

Node node("home-office", 12);

void setup()
{
  Serial.begin(115200);
  InitWiFi("AbuJaberHome", "");
  InitFireBase("arduino-iot-2019.firebaseio.com", "");
}

void loop()
{
  node.SendData();
  delay(60000);
}
