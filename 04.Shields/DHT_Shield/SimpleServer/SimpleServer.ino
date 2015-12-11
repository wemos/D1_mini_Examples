/* WeMos DHT Server
 *
 * Connect to WiFi and respond to http requests with temperature and humidity
 *
 * Based on Adafruit ESP8266 Temperature / Humidity Webserver
 * https://learn.adafruit.com/esp8266-temperature-slash-humidity-webserver
 *
 * Depends on Adafruit DHT Arduino library
 * https://github.com/adafruit/DHT-sensor-library
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTTYPE DHT11   // DHT Shield uses DHT 11
#define DHTPIN D4       // DHT Shield uses pin D4

// Existing WiFi network
const char* ssid     = "YourRouterSSID";
const char* password = "YourRouterPassword";

// Listen for HTTP requests on standard port 80
ESP8266WebServer server(80);

// Initialize DHT sensor
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

float humidity, temperature;                 // Raw float values from the sensor
char str_humidity[10], str_temperature[10];  // Rounded sensor values and as strings
// Generally, you should use "unsigned long" for variables that hold time
unsigned long previousMillis = 0;            // When the sensor was last read
const long interval = 2000;                  // Wait this long until reading again

void handle_root() {
  server.send(200, "text/plain", "WeMos DHT Server. Get /temp or /humidity");
  delay(100);
}

void read_sensor() {
  // Wait at least 2 seconds seconds between measurements.
  // If the difference between the current time and last time you read
  // the sensor is bigger than the interval you set, read the sensor.
  // Works better than delay for things happening elsewhere also.
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you read the sensor
    previousMillis = currentMillis;

    // Reading temperature and humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    humidity = dht.readHumidity();        // Read humidity as a percent
    temperature = dht.readTemperature();  // Read temperature as Celsius

    // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Convert the floats to strings and round to 2 decimal places
    dtostrf(humidity, 1, 2, str_humidity);
    dtostrf(temperature, 1, 2, str_temperature);

    Serial.print("Humidity: ");
    Serial.print(str_humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(str_temperature);
    Serial.println(" °C");
  }
}

void setup(void)
{
  // Open the Arduino IDE Serial Monitor to see what the code is doing
  Serial.begin(9600);
  dht.begin();

  Serial.println("WeMos DHT Server");
  Serial.println("");

  // Connect to your WiFi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Initial read
  read_sensor();

  // Handle http requests
  server.on("/", handle_root);

  server.on("/temp", [](){
    read_sensor();
    char response[50];
    snprintf(response, 50, "Temperature: %s °C", str_temperature);
    server.send(200, "text/plain", response);
  });

  server.on("/humidity", [](){
    read_sensor();
    char response[50];
    snprintf(response, 50, "Humidity: %s %", str_humidity);
    server.send(200, "text/plain", response);
  });

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  // Listen for http requests
  server.handleClient();
}
