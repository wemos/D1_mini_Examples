#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"

SSD1306Wire display(0x3D, SDA, SCL);

void setup() {
  // put your setup code here, to run once:

}

void loop() {

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  display.clear();

  // Font Demo1
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hello world");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello world");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 26, "Hello world");

  display.display();

  delay(1000);

  display.clear();
  display.display();

  delay(1000);


}
