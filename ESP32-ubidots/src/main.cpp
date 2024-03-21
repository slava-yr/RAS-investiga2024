#include "UbidotsEsp32Mqtt.h"
#include <HTTPClient.h>
#include <UrlEncode.h>
#include "time.h"
#include <Adafruit_AHTX0.h>
#include <Adafruit_MLX90614.h>

/* Constants */
// Wifi
const char *UBIDOTS_TOKEN = "BBUS-G2915in2XhcsKsUwzMrUvmfqWsp4nb";  // Ubidots TOKEN
const char *WIFI_SSID = "redpucp";      // Wi-Fi SSID
const char *WIFI_PASS = "C9AA28BA93";      // Wi-Fi password
// Ubidots
const char *DEVICE_LABEL = "esp32"; // ESP32 
const char *AMB_TEMP_LABEL = "amb_temperature"; // aht10 
const char *AMB_HUM_LABEL = "rel_humidity"; // aht10
const char *BOD_TEMP_LABEL = "body_temp"; // mlx
const String AMB_TEMP_ID = "65f7253c22b0df25a943b6ba";
const String BOD_TEMP_ID = "65f78896fc402642f37a5374";
const char *UBI_TOKEN_API = "BBUS-bVtde0QdG4qcGbS1CP8rfa3MYacQnM"; // Token to use the API (request agg values)
const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds
unsigned long timer;
// Time
const char *ntpServer = "pool.ntp.org"; // NTP Server. To request time.
// WhatsApp 
const String phoneNumber = "+51943402428";
const String apiKey = "8147172"; // WhatsApp API key
/*----------------------------------------------------------------------------*/

/*Definitions*/
Adafruit_AHTX0 aht; 
Adafruit_Sensor *aht_humidity, *aht_temp;
Adafruit_MLX90614 mlx = Adafruit_MLX90614 (); 
Ubidots ubidots(UBIDOTS_TOKEN); // Ubidots

/*--------------------------------------------*/

/*Functions*/
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

// Function that gets current epoch time
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    // Serial.println("Failed to obtain time");
    return(0);
  }
  time(&now);
  return now;
}

void requestAggData(String variableID, String aggregation) // Request aggregated data of the previous 24 hours
{
  // start and end time have to be in POSIX format
  uint64_t end_time = getTime(); // Now
  if (end_time != 0)
  {
    uint64_t start_time = end_time - 24*60*60; // 24 hours before
    String url = "https://industrial.api.ubidots.com/api/v1.6/variables/" + variableID + "/statistics/" + aggregation + "/" + String(start_time*1000) + "/" + String(end_time*1000);
    // Serial.println(url);
    HTTPClient http; // Create HTTPClient object
    http.begin(url);
    
    http.addHeader("X-Auth-Token", UBI_TOKEN_API); // Specify headers
    http.addHeader("Content-Type", "application/json");

    // Check HTTP response
    int httpResponseCode = http.GET();
    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.println(payload); // TODO: Do something with this value
    } else {
      Serial.print("Error in HTTP request. Status code: ");
      Serial.println(httpResponseCode);
    }
    // End request
    http.end();
  }  
}
/*--------------------------------------------------------------------------------------------*/

void setup()
{
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.setDebug(true);  // Debug messages
  timer = millis(); // Iniatilize timer
  configTime(0, 0, ntpServer); // Epoch time
  if (!aht.begin()) {
    Serial.println("No encontró módulo de AHT10/AHT20");
  }
  aht_temp = aht.getTemperatureSensor();
  aht_humidity = aht.getHumiditySensor();
  mlx.begin();
}

void loop()
{
  if (!ubidots.connected())
  {
    ubidots.reconnect(); 
  }
  if (abs(static_cast<long int>(millis() - timer)) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    sensors_event_t humidity;
    sensors_event_t temp;
    aht_humidity->getEvent(&humidity);
    aht_temp->getEvent(&temp);

    float amb_temperature = temp.temperature, amb_humidity = humidity.relative_humidity;
    float body_temp = mlx.readObjectTempC();
    ubidots.add(AMB_TEMP_LABEL, amb_temperature); 
    ubidots.add(AMB_HUM_LABEL, amb_humidity); 
    ubidots.add(BOD_TEMP_LABEL, body_temp);
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  // requestAggData("65f3665f287da5090f3f4726", "max");
  // delay(2000);
}
