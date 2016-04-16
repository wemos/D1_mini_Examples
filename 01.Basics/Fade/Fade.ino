/*
 * Fade
 * Using PWM to fade the onboard LED.
 */

const int ledPin = BUILTIN_LED;  // the onboard LED
int brightness = 0;        // how bright the LED is (0 = full, 512 = dim, 1023 = off)
int fadeAmount = 5;        // how many points to fade the LED by
const int delayMillis = 10;      // how long to pause between each loop

void setup() {
  pinMode(ledPin, OUTPUT);  // initialize onboard LED as output
}

void loop() {
  // set the LED brightness
  analogWrite(ledPin, brightness);

  // increment/decrement the brightness for the next loop
  brightness = brightness + fadeAmount;

  // limit to 10-bit (0-1023)
  if (brightness < 0) brightness = 0;
  if (brightness > 1023) brightness = 1023;

  // reverse the direction of the fading at each end
  if (brightness == 0 || brightness == 1023) {
    fadeAmount = -fadeAmount;
  }

  // pause so you can see each brightness level
  delay(delayMillis);
}
