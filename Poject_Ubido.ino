// Fungsi untuk mendapatkan data temperature
float get_temperature_data() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Error reading temperature!"));
    return 0.0;  // Return default value on error
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(t);
    Serial.println(F("°C"));
    return t;
  }
}

// Fungsi untuk mendapatkan data humidity
float get_humidity_data() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println(F("Error reading humidity!"));
    return 0.0;  // Return default value on error
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.println(F("%"));
    return h;
  }
}

// Fungsi untuk membaca data analog dari air quality sensor
int get_air_quality_data() {
  int analog_data = analogRead(sensor_input);
  Serial.print("Air Quality: ");
  Serial.println(analog_data);
  delay(300);  // Allow sensor to stabilize
  return analog_data;
}

// Fungsi untuk mengirim data ke ubidots
void send_data_to_ubidots(float temperature, float humidity, int air_quality) {
  ubidots.add("temperature", temperature);
  ubidots.add("humidity", humidity);
  ubidots.add("air_quality", air_quality);
  bool result = ubidots.publish(DEVICE_LABEL);
  if (result) {
    Serial.println("Successfully publish data to Server!");
  } else {
    Serial.println("Failed publish data to Server!");
  }
} 

void setup() {
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  dht.begin();
  ubidots.setup();
  ubidots.reconnect();
}

void loop() {
  if (!ubidots.connected()) {
    ubidots.reconnect();
  }

  delay(1000);
  send_data_to_ubidots(get_temperature_data(), get_humidity_data(), get_air_quality_data());
  ubidots.loop();
  delay(5000);
}
