#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "fertilizer_model_micromlgen_RandomForest.h"

LiquidCrystal_I2C lcd(0x3F, 16, 2);

// Fertilizer index → name
const char *fertilizerNames[] = {
    "10-26-26", "14-35-14", "17-17-17", "20-20", "28-28", "DAP", "Urea"};

// Soil and Crop Types
const char *soilTypes[] = {"Black", "Clayey", "Loamy", "Red", "Sandy"};
const char *cropTypes[] = {"Barley", "Cotton", "Ground Nuts", "Maize", "Millets", "Oil seeds", "Paddy", "Pulses", "Sugarcane", "Tobacco", "Wheat"};

int soilIndex = 0;
int cropIndex = 0;
bool inferenceDone = false;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200;

// Button pins (adjust as needed)
const int switchPins[] = {15, 35, 34, 23, 18};                         // GPIOs where switches are connected
const char *switchNames[] = {"UP", "DOWN", "LEFT", "RIGHT", "CENTER"}; // Map names to buttons
const int numSwitches = sizeof(switchPins) / sizeof(switchPins[0]);

bool btnUpState = true, btnDownState = true, btnLeftState = true, btnRightState = true, btnCenterState = true;

// HardwareSerial Serial1(1); // UART1 for communication to another MCU (D4/D5)

void showSelection()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Soil:");
  lcd.print(soilTypes[soilIndex]);
  lcd.setCursor(0, 1);
  lcd.print("Crop:");
  lcd.print(cropTypes[cropIndex]);
}

void setup()
{
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RX = D16, TX = D17
  Serial1.begin(9600, SERIAL_8N1, 5, 4); // RX = GPIO5 (D5), TX = GPIO4 (D4)

  lcd.init();
  lcd.backlight();
  for (int i = 0; i < numSwitches; i++)
  {
    pinMode(switchPins[i], INPUT_PULLUP); // Configure pins with internal pull-up
  }
  showSelection();
}

String readFromSerial2(unsigned long timeoutMillis = 5000)
{
  String result = "";
  unsigned long startTime = millis();
  while (millis() - startTime < timeoutMillis)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();
      result += c;
      startTime = millis();
    }
  }
  return result;
}

void loop()
{
  bool currentUp = digitalRead(switchPins[0]);
  bool currentDown = digitalRead(switchPins[1]);
  bool currentLeft = digitalRead(switchPins[2]);
  bool currentRight = digitalRead(switchPins[3]);
  bool currentCenter = digitalRead(switchPins[4]);

  if (millis() - lastDebounceTime > debounceDelay)
  {
    if (!currentUp && btnUpState)
    {
      soilIndex = (soilIndex + 1) % (sizeof(soilTypes) / sizeof(soilTypes[0]));
      showSelection();
      lastDebounceTime = millis();
    }
    if (!currentDown && btnDownState)
    {
      soilIndex = (soilIndex - 1 + sizeof(soilTypes) / sizeof(soilTypes[0])) % (sizeof(soilTypes) / sizeof(soilTypes[0]));
      showSelection();
      lastDebounceTime = millis();
    }
    if (!currentRight && btnRightState)
    {
      cropIndex = (cropIndex + 1) % (sizeof(cropTypes) / sizeof(cropTypes[0]));
      showSelection();
      lastDebounceTime = millis();
    }
    if (!currentLeft && btnLeftState)
    {
      cropIndex = (cropIndex - 1 + sizeof(cropTypes) / sizeof(cropTypes[0])) % (sizeof(cropTypes) / sizeof(cropTypes[0]));
      showSelection();
      lastDebounceTime = millis();
    }
    if (!currentCenter && btnCenterState)
    {
      if (!inferenceDone)
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Reading Sensor...");

        Serial2.flush();
        while (Serial2.available())
          Serial2.read();
        Serial2.println("sendData");
        String npkData = readFromSerial2(3000);

        float temperature = 0, ph = 7, N = 0, P = 0, K = 0;
        if (npkData.length() > 0)
        {
          int matched = sscanf(npkData.c_str(), "tem-%f,ph-%f,n-%f,p-%f,k-%f", &temperature, &ph, &N, &P, &K);
          if (matched == 5)
          {
            float humidity = 50;
            float moisture = 40;

            float input[] = {
                temperature / 100.0,
                humidity,
                moisture,
                (float)soilIndex,
                (float)cropIndex,
                N / 10.0,
                K / 10.0,
                P / 10.0};

            unsigned long startInfer = millis();
            int prediction = model.predict(input);
            unsigned long inferTime = millis() - startInfer;

            lcd.clear();
            lcd.setCursor(0, 0);
            if (prediction >= 0 && prediction < sizeof(fertilizerNames) / sizeof(fertilizerNames[0]))
            {
              lcd.print(fertilizerNames[prediction]);
              // Prepare data string
              char message[100];
              snprintf(message, sizeof(message), "T:%.2f PH:%.2f N:%.2f P:%.2f K:%.2f", temperature, ph, N, P, K);

              // Send to another MCU
              Serial1.println(message);
            }
            else
            {
              lcd.print("Invalid result");
            }

            lcd.setCursor(0, 1);
            lcd.print("Time: ");
            lcd.print(inferTime);
            lcd.print("ms");

            inferenceDone = true;
          }
          else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Parse error");
          }
        }
        else
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("No data recv");
        }
      }
      else
      {
        inferenceDone = false;
        showSelection();
      }
      lastDebounceTime = millis();
    }
  }

  btnUpState = currentUp;
  btnDownState = currentDown;
  btnLeftState = currentLeft;
  btnRightState = currentRight;
  btnCenterState = currentCenter;
}
