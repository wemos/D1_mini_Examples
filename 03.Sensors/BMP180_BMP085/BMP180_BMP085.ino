/*
 * Digital barometric pressure and temperature sensor with I2C interface.
 * The Adafruit_BMP085 library supports both the Bosch BMP085 and BMP180 sensors.
 * The BMP085 has been discontinued and replaced with the BMP180 which is smaller and less expensive but is identical in terms of wiring and software.
 *
 * Features:
 * Pressure range: 300-1100 hPa (-500m to +9000m above sea level)
 * Supply voltage: 1.8-3.6V
 * Low power: 5µa at 1 sample / sec in standard mode, 0.1µa in stand by
 * Up to 0.03hPa / 0.25m resolution
 * -40 to +85°C operational range, ±2°C temperature accuracy
 *
 * Uses I2C address 0x77
 *
 * Connections:
 * D1 Mini     BMP180 / BMP085
 * D1 (SCL) -- SCL
 * D2 (SDA) -- SDA
 * 3V3 ------- VCC
 * G --------- GND
 *
 * Dependencies:
 * https://github.com/adafruit/Adafruit-BMP085-Library
 */

/***************************************************
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout
  ----> https://www.adafruit.com/products/391
  ----> http://www.adafruit.com/products/1603

  These displays use I2C to communicate, 2 pins are required to interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
    while (1) {}
  }
}

void loop() {
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sea level (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(101500));
  Serial.println(" meters");

  Serial.println();
  delay(500);
}
