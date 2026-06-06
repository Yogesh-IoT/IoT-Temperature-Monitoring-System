#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;


const char* topic = "yogesh/temp";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP32_Client")) {
      Serial.println("MQTT Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(9600);   
  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available()) {

    String temp = Serial.readStringUntil('\n');
    temp.trim();  

    Serial.println("Received: " + temp);

    boolean status = client.publish(topic, temp.c_str());

    if (status) {
      Serial.println("Published successfully!");
    } else {
      Serial.println("Publish failed!");
    }

    delay(2000); // small delay (not like ThingSpeak)
  }
}
