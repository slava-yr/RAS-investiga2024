#include <Arduino.h>
#include "UbidotsEsp32Mqtt.h"
#include <HTTPClient.h>
#include <UrlEncode.h>

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

// For WhatsApp 
String phoneNumber = "+51943402428";
String apiKey = "8147172";

void sendMessage(String message){
  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();
  timer = millis(); // Iniatilize timer
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
    // String mensaje = "Valor actualizado en Ubidots: " + String(value);
    // sendMessage(mensaje);
    timer = millis();
  }
  // ubidots.loop();
}
