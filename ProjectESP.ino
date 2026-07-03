#include <WiFi.h>
#include <HTTPClient.h>

const char* serverURL = "https://example.com/api/data";

void setup() {
  // Inisialisasi koneksi WiFi
  WiFi.begin("SSID", "password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
}

void loop() {
  // Membuat objek HTTPClient
  HTTPClient http;

  // Kirim GET request ke server
  http.begin(serverURL);
  int httpCode = http.GET();

  // Baca response dari server
  String payload = http.getString();
  Serial.println(payload);

  // Menutup koneksi
  http.end();

  delay(5000); // Tunggu 5 detik sebelum mengirim request berikutnya
}
