#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"

/* Constants */
const char *UBIDOTS_TOKEN = "BBUS-G2915in2XhcsKsUwzMrUvmfqWsp4nb";  // Ubidots TOKEN
const char *WIFI_SSID = "dlink-3050";      // Wi-Fi SSID
const char *WIFI_PASS = "hjupb35239";      // Wi-Fi password
const char *DEVICE_LABEL = "esp32";   
const char *VARIABLE_LABEL = "potvalue"; 

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds
unsigned long timer;

Ubidots ubidots(UBIDOTS_TOKEN); // Intialize ubidots

uint8_t analogPin = 36;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
}

void loop()
{
  if (!ubidots.connected())
  {
    ubidots.reconnect(); 
  }
  if (abs(static_cast<long int>(millis() - timer)) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, value); 
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  // ubidots.loop();
}
