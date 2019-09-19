#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer server(80);

void InitWiFi(const String &ssid, const String &password) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    delay(300);
  Serial.println("Connected with IP: " + WiFi.localIP().toString());
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  InitWiFi("", "");

  server.on("/lamp", []() {
    digitalWrite(LED_BUILTIN, server.arg(0) == "1" ? LOW : HIGH);
    server.send(200, "text/plain", "Changed LED");
  });
  server.begin();
}

void loop() { server.handleClient(); }
