/*
 * 1 Button Shield - Switch Library
 * Examples using Albert van Dalen's Switch Library
 * http://www.avdweb.nl/arduino/hardware-interfacing/simple-switch-debouncer.html
 *
 * External pull-up resistors are not required.
 * Supports also long press and double clicks.
 * Performs not just de-bouncing, but also de-glitching against EMC pulses.
 *
 * Licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 *
 * 1 Button Shield pushbutton connects pin D3 to GND
 */

#include "Switch.h"

const byte buttonPin = D3;

int i;

Switch button = Switch(buttonPin);  // Switch between a digital pin and GND

void setup() {
  Serial.begin(9600);
  Serial.println("Examples using Switch library");
}

void loop() {
  button.poll();

  if (button.switched()) {
    Serial.print("switched ");
  }

  if (button.pushed()) {
    Serial.print("pushed ");
    Serial.print(++i);
    Serial.print(" ");
  }

  if (button.longPress()) {
    Serial.print("longPress ");
  }

  if (button.doubleClick()) {
    Serial.print("doubleClick ");
  }

  if (button.released()) {
    Serial.print("released\n");
  }
}
