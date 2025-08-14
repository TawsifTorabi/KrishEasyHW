#include <LoRa.h>
#include <SPI.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

// ---------- LoRa Configuration ----------
#define LORA_SS 5
#define LORA_RST 26
#define LORA_DIO0 2
#define LORA_BAND 433E6
#define DEVICE_ID 42069

// ---------- GPS UART (Serial2) ----------
#define GPS_RX 16
#define GPS_TX 17
HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

// ---------- NPK UART (Serial1) ----------
#define NPK_RX 21
#define NPK_TX 22
HardwareSerial npkSerial(1);

// ---------- Buffers and Timing ----------
String npkBuffer = "";
unsigned long lastGPSRead = 0;

void setup() {
  Serial.begin(115200);

  // Start UARTs
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  npkSerial.begin(9600, SERIAL_8N1, NPK_RX, NPK_TX);

  // Setup LoRa
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  while (!LoRa.begin(LORA_BAND)) {
    Serial.println("LoRa init failed. Retrying...");
    delay(1000);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initialized");

  // Indicate Ready
  LoRa.beginPacket();
  LoRa.print("NodeActive-");
  LoRa.print(DEVICE_ID);
  LoRa.endPacket();
}

void loop() {
  // --- Read GPS Non-Blocking ---
  unsigned long start = millis();
  while (gpsSerial.available() && millis() - start < 10) {
    gps.encode(gpsSerial.read());
  }

  // --- Read NPK Serial ---
  while (npkSerial.available()) {
    char c = npkSerial.read();
    if (c == '\n') {
      npkBuffer.trim();
      if (npkBuffer.length() > 0) {
        Serial.println("[NPK] " + npkBuffer);

        // Send GPS info
        if (gps.location.isValid()) {
          String gpsMessage = String(DEVICE_ID) + "|Lat:" + String(gps.location.lat(), 6)
                            + ",Lng:" + String(gps.location.lng(), 6);
          Serial.println("[LoRa TX] " + gpsMessage);
          LoRa.beginPacket();
          LoRa.print(gpsMessage);
          LoRa.endPacket();
          delay(50); // Short delay between packets
        } else {
          Serial.println("[GPS] Invalid or not locked.");
        }

        // Send NPK info
        String npkMessage = String(DEVICE_ID) + "|NPK:" + npkBuffer;
        Serial.println("[LoRa TX] " + npkMessage);
        LoRa.beginPacket();
        LoRa.print(npkMessage);
        LoRa.endPacket();
        delay(50); // Short delay between packets
      }

      // Reset buffer
      npkBuffer = "";
    } else {
      npkBuffer += c;
    }
  }

  delay(10);  // CPU yield
}
