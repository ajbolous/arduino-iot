#include <DHTesp.h>

class Node {
public:
  Node(const String &name, int dht_pin)
      : name_(name), node_path_("/nodes/" + name), data_path_("/data/" + name) {
    dht_.setup(dht_pin, DHTesp::DHT22);
  }

  bool SendData() {
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
