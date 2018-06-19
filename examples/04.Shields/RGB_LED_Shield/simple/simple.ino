//Install [Adafruit_NeoPixel_Library](https://github.com/adafruit/Adafruit_NeoPixel) first.

#include <Adafruit_NeoPixel.h>

#define PIN   D4
#define LED_NUM 7

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  leds.begin(); // This initializes the NeoPixel library.
}



void led_set(uint8 R, uint8 G, uint8 B) {
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, leds.Color(R, G, B));
    leds.show();
    delay(50);
  }
}

void loop() {

  led_set(10, 0, 0);//red
  led_set(0, 0, 0);

  led_set(0, 10, 0);//green
  led_set(0, 0, 0);

  led_set(0, 0, 10);//blue
  led_set(0, 0, 0);

}

