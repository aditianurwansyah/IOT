// Konstan untuk UBIDOTS
const char *UBIDOTS_TOKEN = "UBIDOTS-TOKEN-ANDA";
const char *DEVICE_LABEL = "NAMA-DEVICE-LABEL-PADA-UBIDOTS";

// Konstan untuk WiFi credentials
const char *WIFI_SSID = "WIFI-SSID";
const char *WIFI_PASS = "WIFI-PASSWORD";

// Pin assignments
int sensor_input = 34;
#define DHTPIN 27  // DHT22 sensor pin
#define DHTTYPE DHT22  // DHT sensor type

// Global objects
DHT dht(DHTPIN, DHTTYPE);
Ubidots ubidots(UBIDOTS_TOKEN);
