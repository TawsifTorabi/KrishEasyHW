#include <SPI.h>
#include <LoRa.h>

#define LED_PIN 2
#define SS      5   // LoRa NSS (CS) pin
#define RST     14  // LoRa RESET pin
#define DIO0    2   // LoRa DIO0 (can also be another pin)

bool ledOn = false;
unsigned long ledStartTime = 0;
const unsigned long LED_DURATION = 200; // ms

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Gateway Initializing...");

  // Setup LoRa module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }

  Serial.println("LoRa init success.");
}

void loop() {
  // Check for incoming message
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String message = "";
    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();
    Serial.print("rssi:'");
    Serial.print(rssi);
    Serial.print("':'");
    Serial.print(message);
    Serial.println("'");

    flashLED();
  }

  // Example: send message every 10 seconds (you can remove or modify this)
  static unsigned long lastSendTime = 0;
  const unsigned long sendInterval = 10000; // 10s
  if (millis() - lastSendTime > sendInterval) {
    sendMessage("Hello from gateway");
    lastSendTime = millis();
  }

  updateLED(); // Manage LED non-blocking timer
}

void sendMessage(const String &msg) {
  LoRa.beginPacket();
  LoRa.print(msg);
  LoRa.endPacket();

  Serial.println("Sent: " + msg);
  flashLED();
}

void flashLED() {
  digitalWrite(LED_PIN, HIGH);
  ledOn = true;
  ledStartTime = millis();
}

void updateLED() {
  if (ledOn && millis() - ledStartTime >= LED_DURATION) {
    digitalWrite(LED_PIN, LOW);
    ledOn = false;
  }
}
