#include <TensorFlowLite_ESP32.h>
#include "fertilizer_model.cc" // You must convert your .tflite model to a C array using xxd or xxd.py

#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
// #include "tensorflow/lite/version.h"

// Globals
tflite::MicroErrorReporter error_reporter;
tflite::ErrorReporter* reporter = &error_reporter;

const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;

TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

// Tensor arena
constexpr int kTensorArenaSize = 4 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("ESP32 TensorFlow Lite NPK Inference");

  model = tflite::GetModel(fertilizer_model_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    reporter->Report("Model version mismatch!");
    while (true);
  }

  static tflite::MicroMutableOpResolver<4> resolver;
  resolver.AddBuiltin(tflite::BuiltinOperator_FULLY_CONNECTED, tflite::ops::micro::Register_FULLY_CONNECTED());
  resolver.AddBuiltin(tflite::BuiltinOperator_SOFTMAX, tflite::ops::micro::Register_SOFTMAX());
  resolver.AddBuiltin(tflite::BuiltinOperator_RESHAPE, tflite::ops::micro::Register_RESHAPE());
  resolver.AddBuiltin(tflite::BuiltinOperator_DEQUANTIZE, tflite::ops::micro::Register_DEQUANTIZE());

  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize, reporter);
  interpreter = &static_interpreter;

  interpreter->AllocateTensors();

  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("Ready. Enter N,P,K as CSV (e.g., 70,25,40):");
}

void loop() {
  if (Serial.available()) {
    String csv = Serial.readStringUntil('\n');
    csv.trim();
    float npk[3];
    int count = 0;

    char* token = strtok((char*)csv.c_str(), ",");
    while (token != nullptr && count < 3) {
      npk[count++] = atof(token);
      token = strtok(nullptr, ",");
    }

    if (count != 3) {
      Serial.println("Invalid input. Enter as: N,P,K");
      return;
    }

    // Assign to model input
    for (int i = 0; i < 3; i++) {
      input->data.f[i] = npk[i];
    }

    // Run inference
    TfLiteStatus invoke_status = interpreter->Invoke();
    if (invoke_status != kTfLiteOk) {
      Serial.println("Invoke failed!");
      return;
    }

    // Read output
    int predicted_class = 0;
    float max_score = output->data.f[0];
    for (int i = 1; i < output->dims->data[1]; i++) {
      if (output->data.f[i] > max_score) {
        max_score = output->data.f[i];
        predicted_class = i;
      }
    }

    const char* fertilizers[] = {"Nitrogen", "Phosphorus", "Potassium"};
    Serial.print("Recommended fertilizer: ");
    Serial.println(fertilizers[predicted_class]);
  }
}
