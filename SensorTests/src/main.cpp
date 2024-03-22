#include <Adafruit_AHTX0.h>
#include <Adafruit_MLX90614.h>
Adafruit_AHTX0 aht; 

Adafruit_MLX90614 mlx = Adafruit_MLX90614 (); 
Adafruit_Sensor *aht_humidity, *aht_temp;


void setup() {
  Serial.begin(115200);
  mlx.begin();
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit AHT10/AHT20 test!");

  if (!aht.begin()) {
    Serial.println("No encontró módulo de AHT10/AHT20");
    while (1) {
      delay(10);
    }
  }

  Serial.println("AHT10/AHT20 enconntrado!");
  aht_temp = aht.getTemperatureSensor();
  // aht_temp->printSensorDetails();

  aht_humidity = aht.getHumiditySensor();
  // aht_humidity->printSensorDetails();

}

void loop() {
  sensors_event_t humidity;
  sensors_event_t temp;
  aht_humidity->getEvent(&humidity);
  aht_temp->getEvent(&temp);

  /* Display the results (humidity is measured in % relative humidity (% rH) */
  Serial.print("\t\tHumidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" % rH");
  Serial.print("\t\tTemperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degrees C");

  Serial.print("\t\tBody Temperature: ");
  Serial.print(mlx.readObjectTempC());
  Serial.println(" degrees C");
  delay(1000);

}