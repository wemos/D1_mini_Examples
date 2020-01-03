/*
  Install Adafruit_SGP30 First: https://github.com/adafruit/Adafruit_SGP30
*/

#include <Adafruit_SGP30.h>
#include <Wire.h>

Adafruit_SGP30 sgp30;

void setup()
{
  Serial.begin(9600);

  if (!sgp30.begin())
  {
    Serial.println("\r\nSensor not found :(");
    while (1)
      ;
  }
  Serial.print("Found SGP30 serial #");
  Serial.print(sgp30.serialnumber[0], HEX);
  Serial.print(sgp30.serialnumber[1], HEX);
  Serial.println(sgp30.serialnumber[2], HEX);
}

void loop()
{

  //CO2: 400 ppm  TVOC: 0 ppb
  delay(1000); //Wait 1 second
  if (sgp30.IAQmeasure())
  {

    Serial.print("CO2: ");
    Serial.print(sgp30.eCO2);
    Serial.print(" ppm\tTVOC: ");
    Serial.print(sgp30.TVOC);
    Serial.println(" ppb");
  }
  else
  {
    Serial.println("Error...\r\n");
    while (1)
      ;
  }
}
