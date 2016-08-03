/* DHT Shield - Deep Sleep
 *
 * Displays humidity, temperature and heat index, sleeps for 10 seconds and repeats
 *
 * Connections:
 * D0 -- RST
 *
 * If you cant reprogram as the ESP is sleeping, disconnect D0 - RST and try again
 *
 * Depends on Adafruit DHT Arduino library
 * https://github.com/adafruit/DHT-sensor-library
 */

#include "DHT.h"
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// sleep for this many seconds
const int sleepSeconds = 10;

float humidity, temperature, heatIndex;
char str_humidity[10], str_temperature[10], str_heatIndex[10];

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nWake up");

  // Connect D0 to RST to wake up
  pinMode(D0, WAKEUP_PULLUP);

  Serial.println("Initialize DHT sensor");
  dht.begin();
  delay(2000);

  Serial.println("Read DHT sensor");
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  }
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  // Convert the floats to strings and round to 2 decimal places
  dtostrf(humidity, 1, 2, str_humidity);
  dtostrf(temperature, 1, 2, str_temperature);
  dtostrf(heatIndex, 1, 2, str_heatIndex);

  Serial.printf("Humidity:    %s %%\nTemperature: %s *C\nHeat index:  %s *C\n", str_humidity, str_temperature, str_heatIndex);
  Serial.printf("Sleep for %d seconds\n\n", sleepSeconds);

  // convert to microseconds
  ESP.deepSleep(sleepSeconds * 1000000);
}

void loop() {
}
