#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LOLIN_HP303B.h>

LOLIN_HP303B HP303B;

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

void setup()
{

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);

    //Address of the HP303B (0x77 or 0x76)
    HP303B.begin(); // I2C address = 0x77
    // HP303B.begin(0x76); //I2C address = 0x76
}

void loop()
{

    HP303B.begin();
    // Clear the buffer.
    display.clearDisplay();
    display.setCursor(0, 0);
    

    int32_t temperature;
    int32_t pressure;
    int16_t oversampling = 7;
    int16_t ret;

    ret = HP303B.measureTempOnce(temperature, oversampling);

    if (ret != 0)
    {
        display.setTextSize(1);
        display.println("T: error");
    }
    else
    {
        display.setTextSize(1);
        display.println("T: ");
        display.setTextSize(2);
        display.println(temperature);
    }

    ret = HP303B.measurePressureOnce(pressure, oversampling);

    if (ret != 0)
    {
        display.setTextSize(1);
        display.println("P: error");
    }
    else
    {
        display.setTextSize(1);
        display.println("P: ");
        display.setTextSize(2);
        display.println(pressure);
    }

    display.display();
    delay(1000);
}