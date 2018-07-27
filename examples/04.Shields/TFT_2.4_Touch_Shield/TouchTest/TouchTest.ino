/***************************************************

Setup Adafruit_GFX, Adafruit_ILI9341 and XPT2046_Touchscreen Library first:

https://github.com/adafruit/Adafruit-GFX-Library

https://github.com/adafruit/Adafruit_ILI9341

https://github.com/PaulStoffregen/XPT2046_Touchscreen

****************************************************/

#include <SPI.h>
#include <XPT2046_Touchscreen.h>


#define TS_CS  D3


XPT2046_Touchscreen ts(TS_CS);


void setup() {
  Serial.begin(115200);
  ts.begin();
  ts.setRotation(1);
  while (!Serial && (millis() <= 1000));
}

void loop() {
  if (ts.touched()) {
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

