#include <SoftwareSerial.h>
#include <Wire.h>

// RS485 RE/DE control pins
#define RE 8
#define DE 7

// Modbus RTU requests
const byte temp[]  = {0x01, 0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA};
const byte ph[]    = {0x01, 0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A};
const byte nitro[] = {0x01, 0x03, 0x00, 0x04, 0x00, 0x01, 0xC5, 0xCB};
const byte phos[]  = {0x01, 0x03, 0x00, 0x05, 0x00, 0x01, 0x94, 0x0B};
const byte pota[]  = {0x01, 0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B};

byte values[11];

SoftwareSerial mod(2, 3); // RX, TX

String serialInput = "";

void setup() {
  Serial.begin(9600);
  mod.begin(4800);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  digitalWrite(RE, LOW);
  digitalWrite(DE, LOW);
  delay(500);
}

void loop() {
  // Listen for serial input
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      serialInput.trim();

      if (serialInput == "sendData") {
        // Call sensors only when requested
        uint16_t nitrogenVal = readSensor(nitro);
        delay(200);
        uint16_t phosphorusVal = readSensor(phos);
        delay(200);
        uint16_t potassiumVal = readSensor(pota);
        delay(200);
        uint16_t tempVal = readSensor(temp);
        delay(200);
        uint16_t phVal = readSensor(ph);
        delay(200);

        // Output in requested format
        Serial.print("tem-"); Serial.print(tempVal);
        Serial.print(",ph-"); Serial.print(phVal / 10.0, 1);
        Serial.print(",n-");  Serial.print(nitrogenVal);
        Serial.print(",p-");  Serial.print(phosphorusVal);
        Serial.print(",k-");  Serial.println(potassiumVal);
      }

      serialInput = "";  // Clear input
    } else {
      serialInput += ch;
    }
  }
}

// ---- Sensor Reading Function ----
uint16_t readSensor(const byte *cmd) {
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(10);

  mod.write(cmd, 8);
  delay(10);

  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);

  int i = 0;
  unsigned long startTime = millis();
  while (mod.available() == 0) {
    if (millis() - startTime > 1000) return 0; // Timeout
  }

  while (mod.available() && i < 7) {
    values[i++] = mod.read();
  }

  if (i >= 5) {
    return (values[3] << 8) | values[4];  // Combine MSB and LSB
  }

  return 0;
}
