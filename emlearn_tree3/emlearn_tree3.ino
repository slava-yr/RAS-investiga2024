#include "decision_tree_3.h"

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // Se definen las features
  const float features[] = { a, b }; 

  // Predicción
  const int32_t out = xor_model_predict(features, 2);
  

}
