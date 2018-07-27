/***************************************************

Setup Adafruit_GFX, Adafruit_ILI9341 and XPT2046_Touchscreen Library first:

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit_ILI9341

https://github.com/PaulStoffregen/XPT2046_Touchscreen

****************************************************/


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

#define TFT_CS D0
#define TFT_DC D8
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define TS_CS  D3
XPT2046_Touchscreen ts(TS_CS);


void setup() {
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Touch Test");

  while (!Serial && (millis() <= 1000));
}

void loop() {
  if (ts.touched()) {
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

