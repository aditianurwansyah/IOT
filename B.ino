#include <WiFi.h>
#include <PubSubClient.h>

// Deklarasi variabel
const char* ssid = "Simanjuntak-Family";
const char* password = "22130424";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* topic = "/test/esp32/topik2";
const char* mqtt_username = "ajdsjfaopsdvmoasdpvaspdojf";
const char* mqtt_password = "";


// Buat objek WiFiClient
WiFiClient wifiClient;

// Buat objek PubSubClient
PubSubClient client(wifiClient);

void setup() {
  Serial.begin(115200);

  // Hubungkan ESP32 ke WiFi
  WiFi.begin(ssid, password);

  // Cek status koneksi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Tampilkan pesan sukses
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP address: " + WiFi.localIP().toString());

  // Hubungkan ESP32 ke broker MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Lakukan koneksi ke broker MQTT
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32", mqtt_username, mqtt_password)) {
      Serial.println("MQTT connected!");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
  // Subscribe data
  client.subscribe(topic, 0);
}

void loop() {
  client.loop();
}

// Callback ketika ada pesan yang diterima dari broker
void callback(char* topic, byte* payload, unsigned int length) {
  // Tampilkan pesan yang diterima
  Serial.print("Received topic: ");
  Serial.println(topic);
  Serial.print("Received payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
