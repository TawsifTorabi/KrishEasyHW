// #include <Arduino.h>
// // #include "fertilizer_model_micromlgen_DecisionTree.h"
// #include "fertilizer_model_micromlgen_RandomForest.h"

// // Fertilizer index → name
// const char *fertilizerNames[] = {
//     "10-26-26",
//     "14-35-14",
//     "17-17-17",
//     "20-20",
//     "28-28",
//     "DAP",
//     "Urea"
// };

// // Soil Type name → index mapping (same as in training)
// const char *soilTypes[] = {
//     "Black",    // 0
//     "Clayey",    // 1
//     "Loamy",    // 2
//     "Red",      // 3
//     "Sandy"    // 4
// };

// int selectedSoilType = -1;
// bool soilTypeSet = false;

// void askSoilType() {
//   Serial.println("Select Soil Type by index:");
//   for (int i = 0; i < sizeof(soilTypes) / sizeof(soilTypes[0]); i++) {
//     Serial.print(i);
//     Serial.print(" → ");
//     Serial.println(soilTypes[i]);
//   }
//   Serial.print("Enter soil type index: ");
// }

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   askSoilType();
// }

// String inputString = "";
// int stage = 0;
// float N, P, K;

// void loop() {
//   if (Serial.available()) {
//     char c = Serial.read();

//     if (c == '\n' || c == '\r') {
//       inputString.trim();

//       if (!soilTypeSet) {
//         selectedSoilType = inputString.toInt();
//         if (selectedSoilType >= 0 && selectedSoilType < (sizeof(soilTypes) / sizeof(soilTypes[0]))) {
//           soilTypeSet = true;
//           Serial.print("Selected Soil Type: ");
//           Serial.println(soilTypes[selectedSoilType]);
//           Serial.println("Enter Nitrogen value (N): ");
//         } else {
//           Serial.println("Invalid index. Try again.");
//           askSoilType();
//         }
//       } else {
//         switch (stage) {
//           case 0:
//             N = inputString.toFloat();
//             Serial.println("Enter Phosphorous value (P): ");
//             stage++;
//             break;
//           case 1:
//             P = inputString.toFloat();
//             Serial.println("Enter Potassium value (K): ");
//             stage++;
//             break;
//           case 2:
//             K = inputString.toFloat();

//             // All inputs are collected, now predict
//             Serial.println("Predicting fertilizer...");

//             // Set default/sample values
//             float temperature = 30;
//             float humidity = 50;
//             float moisture = 40;
//             int cropType = 1;  // Example crop (should match label-encoded index from training)

//             float input[] = {
//               temperature,
//               humidity,
//               moisture,
//               (float)selectedSoilType,
//               (float)cropType,
//               N,
//               K,
//               P
//             };

//             int prediction = model.predict(input);

//             Serial.print("Predicted Fertilizer Index: ");
//             Serial.println(prediction);

//             if (prediction >= 0 && prediction < sizeof(fertilizerNames) / sizeof(fertilizerNames[0])) {
//               Serial.print("Predicted Fertilizer Name: ");
//               Serial.println(fertilizerNames[prediction]);
//             } else {
//               Serial.println("Prediction out of range.");
//             }

//             // Reset for next run
//             stage = 0;
//             soilTypeSet = false;
//             Serial.println("\n--- Restarting ---");
//             askSoilType();
//             break;
//         }
//       }

//       inputString = "";  // clear buffer`
//     } else {
//       inputString += c;
//     }
//   }
// }
