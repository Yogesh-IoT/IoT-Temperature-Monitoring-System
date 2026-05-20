#include <WiFi.h>   // ✅ Correct for ESP32

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASS";
String apiKey = "YOUR_API_KEY";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  if (Serial.available()) {
    String temp = Serial.readStringUntil('\n');

    if (client.connect("api.thingspeak.com", 80)) {
      String url = "/update?api_key=" + apiKey + "&field1=" + temp;

      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: api.thingspeak.com\r\n" +
                   "Connection: close\r\n\r\n");
    }
  }
}