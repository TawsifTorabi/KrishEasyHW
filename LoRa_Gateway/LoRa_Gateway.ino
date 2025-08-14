#include <SPI.h>
#include <LoRa.h>

#define LED_PIN 2
#define LORA_SS 5
#define LORA_RST 14
#define LORA_DIO0 2

const unsigned long LED_DURATION = 100; // ms
bool ledOn = false;
unsigned long ledStartTime = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  while (!Serial);  // Wait for Serial to be ready

  Serial.println("LoRa Gateway Initializing...");

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (true); // halt
  }

  Serial.println("LoRa init success.");
}

void loop() {
  // 🔹 Check LoRa first
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    String message;
    message.reserve(packetSize);

    while (LoRa.available()) {
      message += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();

    Serial.print("msg:");
    Serial.print(rssi);
    Serial.print(":'");
    Serial.print(message);
    Serial.println("'");

    flashLED();
  }

  // 🔹 Handle Serial command (non-blocking)
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "isGateway") {
      Serial.println("GatewayTrue");
    }
  }

  updateLED();
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
