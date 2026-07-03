#include <WiFi.h>
#include <PubSubClient.h>

// Deklarasi variabel
const char* ssid = "YOUR-SSID";
const char* password = "YOUR-WIFI-PASSWORD";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* topic = "/test/joshua/topicku";
const char* mqtt_username = "test";
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
}

void loop() {
  //publish data ke server
  String data = "Hello, world!";
  client.publish(topic, data.c_str());
  Serial.println("Data published");
  delay(5000);

}
