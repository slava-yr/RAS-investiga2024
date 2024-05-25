#include "decision_tree_3.h"
#define LED_BUILTIN 2

const int ledPin = LED_BUILTIN;

void setup() {
  Serial.begin(115200); // For esp32
  pinMode(ledPin, OUTPUT); 
}

float cardioDisease; // Cardiovascular disease history
float heatIndex; // Heat Index
float envTemp; // Environmental temperature (C)
float weight; 
float temp; // Patient temperature
float relHum; // Relative humidity
float age; 

//float x[7] = {0, 107.3, 39, 48.36, 40.8, 0.4, 38}; // Predice 1
float x[7] = {0, 0, 0, 0, 0, 0, 0}; // Predice 0

void loop() {
  
  int32_t out = tree_3_predict(x, 7);
  if (out < 0) {
    Serial.println("ERROR");
  } else {
    Serial.print("Output class:");
    Serial.println(out);
  }
  digitalWrite(ledPin, out == 1 ? HIGH : LOW);
  delay(500);
}
