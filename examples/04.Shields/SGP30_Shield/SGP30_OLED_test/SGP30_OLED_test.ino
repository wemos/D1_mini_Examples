#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_SGP30.h>

#define OLED_RESET 0 // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_SGP30 sgp30; 

void setup()
{

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  if (sgp30.begin() == false)
  {

    while (1)
      ;
  }


}

void loop()
{

  delay(1000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(WHITE);

  if (sgp30.IAQmeasure())
  {

    display.println("CO2: ");
    display.setTextSize(2);

    display.println(sgp30.eCO2);

    display.setTextSize(1);
    display.println("TVOC: ");

    display.setTextSize(2);
    display.println(sgp30.TVOC);

    display.display();
  }
  else
  {
    display.println("Error!");
    display.display();

    while (1)
    {
      ;
    }
    
  }
  
  
}
