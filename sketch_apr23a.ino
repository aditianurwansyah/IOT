#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Alamat I2C untuk MPU6050 dan LCD
const int MPU_ADDR = 0x68;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Umumnya 0x27 atau 0x3F

// Definisi Pin Komponen
const int redLED = 2;
const int greenLED = 3;
const int buzzer = 8; // Buzzer menggunakan Jalur Pin 8 via Resistor

// Variabel untuk menyimpan data Akselerometer MPU6050
float x, y, z;
float last_x, last_y, last_z;

// Batas toleransi gerakan tidur (Aktigrafi)
// Semakin kecil angka ini, sensor akan semakin sensitif mendeteksi gerakan bantal/kasur
float batasGerakan = 1.2; 

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // PROTEKSI: Mencegah MPU6050 macet akibat drop tegangan dari buzzer
  Wire.setWireTimeout(3000, true); 

  // Membangunkan MPU6050 dari mode hemat daya (Sleep Mode)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // Register Manajemen Daya
  Wire.write(0);    // Set ke 0 untuk mengaktifkan sensor
  Wire.endTransmission(true);

  // Mengatur semua pin komponen sebagai OUTPUT
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Inisialisasi Tampilan Layar LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Sistem Dimulai ");
  lcd.setCursor(0, 1);
  lcd.print("  Sleep Monitor ");
  delay(3000);
  lcd.clear();
}

void loop() {
  // Meminta data akselerasi mentah dari MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // Alamat register awal untuk data sumbu X, Y, Z
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); 

  // Menggabungkan byte High dan Low menjadi nilai utuh (integer 16-bit)
  int16_t ax = (Wire.read() << 8 | Wire.read());
  int16_t ay = (Wire.read() << 8 | Wire.read());
  int16_t az = (Wire.read() << 8 | Wire.read());

  // Mengonversi nilai mentah menjadi satuan G-Force (Gravitasi)
  x = ax / 16384.0;
  y = ay / 16384.0;
  z = az / 16384.0;

  // Menghitung selisih getaran/kemiringan dari detik sebelumnya (Absolut)
  float deltaX = abs(x - last_x);
  float deltaY = abs(y - last_y);
  float deltaZ = abs(z - last_z);
  
  // Total akumulasi pergerakan tubuh saat tidur
  float totalGerakan = deltaX + deltaY + deltaZ;

  // --- LOGIKA EVALUASI KUALITAS TIDUR ---
  if (totalGerakan > batasGerakan) {
    // 1. Kondisi: TIDUR GELISAH (Banyak gerakan)
    digitalWrite(redLED, HIGH);   // Lampu Merah MENYALA
    digitalWrite(greenLED, LOW);  // Lampu Hijau MATI
    
    // Tampilan di LCD
    lcd.setCursor(0, 0);
    lcd.print("Status: Gelisah ");
    lcd.setCursor(0, 1);
    lcd.print("Banyak Gerak!   ");
    
    // BUNYIKAN BUZZER: Frekuensi 1000Hz, durasi 200 milidetik
    tone(buzzer, 1000, 200); 
  } else {
    // 2. Kondisi: TIDUR NYENYAK (Tenang / Pulas)
    digitalWrite(redLED, LOW);    // Lampu Merah MATI
    digitalWrite(greenLED, HIGH); // Lampu Hijau MENYALA
    
    // Tampilan di LCD
    lcd.setCursor(0, 0);
    lcd.print("Status: Nyenyak ");
    lcd.setCursor(0, 1);
    lcd.print("Tidur Pulas...  ");
  }

  // Mengirim data ke laptop untuk dipantau secara visual grafik (Serial Plotter)
  Serial.print("Gerakan:");
  Serial.println(totalGerakan);

  // Menyimpan posisi sensor saat ini untuk pembanding pada loop 1 detik berikutnya
  last_x = x;
  last_y = y;
  last_z = z;

  // Interval pengambilan data (setiap 1 detik sekali)
  delay(1000); 
}