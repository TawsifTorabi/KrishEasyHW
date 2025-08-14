const int switchPins[] = {15, 35, 34, 23, 18}; // GPIOs where switches are connected
const char* switchNames[] = {"UP", "DOWN", "LEFT", "RIGHT", "CENTER"}; // Map names to buttons
const int numSwitches = sizeof(switchPins) / sizeof(switchPins[0]);

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numSwitches; i++) {
    pinMode(switchPins[i], INPUT_PULLUP); // Configure pins with internal pull-up
  }
}

void loop() {
  for (int i = 0; i < numSwitches; i++) {
    int state = digitalRead(switchPins[i]);
    if (state == LOW) { // Active LOW, pressed
      Serial.print(switchNames[i]);
      Serial.println(" pressed");
    }
  }
  delay(100); // Debounce and avoid flooding serial mon
}