#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 2
const unsigned long LED_DURATION = 100; // ms
bool ledOn = false;
unsigned long ledStartTime = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  while (!Serial);

  Serial.println("ESP-NOW Gateway Initializing...");

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    while (true);  // halt
  }

  esp_now_register_recv_cb(onReceive);
  Serial.println("ESP-NOW init success.");
}

void loop() {
  // Handle incoming Serial command
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "isGateway") {
      Serial.println("GatewayTrue");
    }
  }

  updateLED();
}

// 🟢 Callback function for receiving ESP-NOW messages
void onReceive(const uint8_t *mac_addr, const uint8_t *data, int len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr),
           "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2],
           mac_addr[3], mac_addr[4], mac_addr[5]);

  String message = "";
  for (int i = 0; i < len; i++) {
    message += (char)data[i];
  }

  Serial.print("msg:");
  Serial.print(macStr);
  Serial.print(":'");
  Serial.print(message);
  Serial.println("'");

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
