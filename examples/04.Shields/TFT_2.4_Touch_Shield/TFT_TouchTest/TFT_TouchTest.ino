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
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#define TFT_CS D0  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_DC D8  //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TFT_RST -1 //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)
#define TS_CS D3   //for D1 mini or TFT I2C Connector Shield (V1.1.0 or later)

// #define TFT_CS 14  //for D32 Pro
// #define TFT_DC 27  //for D32 Pro
// #define TFT_RST 33 //for D32 Pro
// #define TS_CS  12 //for D32 Pro

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TS_CS);

void setup()
{
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Touch Test");

  while (!Serial && (millis() <= 1000))
    ;
}

void loop()
{
  if (ts.touched())
  {
    TS_Point p = ts.getPoint();

    tft.fillScreen(ILI9341_BLACK);
    tft.setCursor(0, 0);

    tft.print("Pressure = ");
    tft.println(p.z);
    tft.print("X = ");
    tft.println(p.x);
    tft.print("Y = ");
    tft.println(p.y);
  }
}
