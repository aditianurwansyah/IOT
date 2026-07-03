#include <WiFi.h>
#include <HTTPClient.h>

const char* serverURL = "https://example.com/api/data";
const char* postData = "key1=value1&key2=value2";

void setup() {
  Serial.begin(115200);
  // Inisialisasi koneksi WiFi
  WiFi.begin("SSID", "password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Buat objek HTTPClient
  HTTPClient http;

  // Set URL server web
  http.begin("https://example.com/api/data");

  // Buat data yang akan dikirimkan
  String data = "{"
                "  \"nama\": \"John Doe\","
                "  \"usia\": 30"
                "}";

  // Kirim permintaan POST
  int httpCode = http.POST(data);

  // Cek status permintaan
  if (httpCode == HTTP_CODE_OK) {
    // Tampilkan pesan sukses
    Serial.println("Data berhasil dikirim");
  } else {
    // Tampilkan pesan kesalahan
    Serial.println("Error: " + String(httpCode));
  }

  // Tutup objek HTTPClient
  http.end();
}

void loop() {
}
