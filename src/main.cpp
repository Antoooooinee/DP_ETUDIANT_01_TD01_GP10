#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 33     // Broche numérique connectée au capteur DHT
#define LED 26       // Broche pour la LED (non utilisée dans cette étape)

#define DHTTYPE    DHT11     // Type de capteur DHT (DHT11, DHT22, ou DHT21)

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;

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

  digitalWrite(LED, HIGH);
  delay(5000);
  digitalWrite(LED, LOW);

  esp_sleep_enable_timer_wakeup(5 * 1000000 - 500);
  esp_deep_sleep_start();
}

void loop() {
  // loop vide
}
