// Use HardwareSerial instance 1 for UART1

void setup() {
  Serial.begin(115200); // USB Serial monitor
  // Initialize UART1 with RX=22, TX=21
  Serial1.begin(9600, SERIAL_8N1, 21, 22); 
  Serial.println("Ready to receive NPK data...");
}

void loop() {
  if (Serial1.available()) {
    String message = Serial1.readStringUntil('\n'); // Read until newline
    Serial.print("Received: ");
    Serial.println(message);
  }
}
