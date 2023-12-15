#include <Wire.h>
#include "SSD1306Wire.h" 
#include <BH1750.h>

SSD1306Wire display(0x3C, SDA, SCL,GEOMETRY_64_48);

BH1750 light(0x23);

void setup() {

  Serial.begin(115200);

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

}

void loop() {

  display.clear();
  

  if (light.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {

    display.drawString(0, 0,"L:"+String(light.readLightLevel()));

  }
  else
  {
    display.drawString(0, 0,"Error!");
  }
  display.display();
  delay(1000);

}
