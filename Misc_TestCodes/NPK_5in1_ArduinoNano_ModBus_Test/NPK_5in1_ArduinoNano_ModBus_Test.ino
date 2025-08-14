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

// SoftwareSerial: RX = D2, TX = D3
SoftwareSerial mod(2, 3);

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
  byte nitrogenVal = nitrogen();
  delay(250);
  byte phosphorusVal = phosphorous();
  delay(250);
  byte potassiumVal = potassium();
  delay(250);
  byte tempVal = readTemperature();
  delay(250);
  byte phVal = readPH();
  delay(250);

  Serial.println("---- Sensor Readings ----");
  Serial.print("Temperature: ");
  Serial.print(tempVal);
  Serial.println(" °C");

  Serial.print("pH: ");
  Serial.println(phVal / 10.0, 1); // convert to float

  Serial.print("Nitrogen: ");
  Serial.print(nitrogenVal);
  Serial.println(" mg/kg");

  Serial.print("Phosphorous: ");
  Serial.print(phosphorusVal);
  Serial.println(" mg/kg");

  Serial.print("Potassium: ");
  Serial.print(potassiumVal);
  Serial.println(" mg/kg");

  Serial.println("------------------------\n");

  delay(3000);
}

// ---- Sensor Reading Functions ----

byte readSensor(const byte *cmd) {
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
    return values[3] << 8 | values[4];  // Combine MSB + LSB
  }

  return 0;
}

byte readTemperature() {
  return readSensor(temp);
}

byte readPH() {
  return readSensor(ph);
}

byte nitrogen() {
  return readSensor(nitro);
}

byte phosphorous() {
  return readSensor(phos);
}

byte potassium() {
  return readSensor(pota);
}
