#include "xor_model.h"
#define LED_BUILTIN 2

const int ledPin = LED_BUILTIN;
const int digitalPinA = 5;
const int digitalPinB = 17;

void setup() {
  pinMode(ledPin, OUTPUT); 
  pinMode(digitalPinA, INPUT_PULLUP); 
  pinMode(digitalPinB, INPUT_PULLUP); 
}

float readDigital(const int pin) {
    return digitalRead(pin) ? 1.0 : 0.0;
}


void loop() {

  const float a = readDigital(digitalPinA);
  const float b = readDigital(digitalPinB);

  const float features[] = { a, b };

  const int32_t out = xor_model_predict(features, 2);

  if (out < 0) {
    Serial.println("ERROR");
  } else {
    Serial.print("Output class:");
    Serial.println(out);
  }
  digitalWrite(ledPin, out == 1 ? HIGH : LOW);
  delay(100);
}
