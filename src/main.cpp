#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33   
#define LED 26       

#define DHTTYPE    DHT11    

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);


  delayMS = sensor.min_delay / 1000;
}

void loop() {
  digitalWrite(LED, HIGH);  

  sensors_event_t event;
  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }

  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  digitalWrite(LED, LOW); 
  
  
  delay(delayMS);
  esp_sleep_enable_timer_wakeup(delayMS * 1000);
  esp_deep_sleep_start();
}
