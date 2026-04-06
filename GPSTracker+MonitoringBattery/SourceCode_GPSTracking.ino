//SOURCE CODE FOR GPS TRACKING

#include <Arduino.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

// 1. Konfigurasi PIN
const int batteryPin = 33; // Pin ADC untuk baterai
const int rxPin = 2;       // RX ESP32 ← TX GPS
const int txPin = 4;       // TX ESP32 → RX GPS

// 2. Objek GPS & Serial
TinyGPSPlus gps;
HardwareSerial SerialGPS(2);

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, rxPin, txPin);

  Serial.println("ESP32 GPS & Battery Monitor (Offline)");
}

void loop() {
  // Membaca data dari modul GPS
  while (SerialGPS.available() > 0) {
    gps.encode(SerialGPS.read());
  }

  // --- A. PROSES DATA BATERAI ---
  int rawADC = analogRead(batteryPin);
  float vOut = (rawADC * 3.3) / 4095.0;
  float vBat = vOut * 2.0; 
  float batteryPercent = ((vBat - 3.2) / (4.2 - 3.2)) * 100.0;
  batteryPercent = constrain(batteryPercent, 0, 100);

  // --- B. PROSES DATA GPS ---
  float lat   = gps.location.isValid() ? gps.location.lat() : 0.0;
  float lng   = gps.location.isValid() ? gps.location.lng() : 0.0;
  float alt   = gps.altitude.isValid() ? gps.altitude.meters() : 0.0;
  float speed = gps.speed.isValid() ? gps.speed.kmph() : 0.0;

  // --- C. TAMPILKAN KE SERIAL MONITOR ---
  Serial.println("===============================");
  Serial.print("Baterai   : "); Serial.print(batteryPercent); Serial.println(" %");
  Serial.print("Latitude  : "); Serial.println(lat, 6);
  Serial.print("Longitude : "); Serial.println(lng, 6);
  Serial.print("Altitude  : "); Serial.print(alt); Serial.println(" m");
  Serial.print("Speed     : "); Serial.print(speed); Serial.println(" km/h");
  Serial.println("===============================");

  delay(3000); // Update setiap 3 detik
}
