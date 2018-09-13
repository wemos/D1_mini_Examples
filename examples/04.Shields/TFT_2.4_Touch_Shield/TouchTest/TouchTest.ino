/***************************************************

1. !!!Make sure you using lastest ESP8266 core for Arduino, otherwise it may not work properly.
  https://github.com/esp8266/Arduino
  
  (The pin D0(GPIO16) will be not work when you use older version ESP8266 core for Arduino, 
  because the older version ESP8266 core for Arduino's digitalPinToBitMask(), portOutputRegister(), 
  portInputRegister() and portModeRegister() fuction have some bugs which Adafruit_ILI9341 Library will use.
  This bug was fixed after commit:  https://github.com/esp8266/Arduino/commit/799193888a553de8876052019842538396f92194 )
    

2. Setup latest Adafruit_GFX, Adafruit_ILI9341 and XPT2046_Touchscreen Library first:

    https://github.com/adafruit/Adafruit-GFX-Library

    https://github.com/adafruit/Adafruit_ILI9341

    https://github.com/PaulStoffregen/XPT2046_Touchscreen

****************************************************/

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#define TS_CS D3 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
// #define TS_CS  12 //for D32 Pro

XPT2046_Touchscreen ts(TS_CS);

void setup()
{
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000))
    ;
}

void loop()
{
  if (ts.touched())
  {
    TS_Point p = ts.getPoint();
    Serial.print("Pressure = ");
    Serial.print(p.z);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.print(p.y);
    delay(30);
    Serial.println();
  }
}
