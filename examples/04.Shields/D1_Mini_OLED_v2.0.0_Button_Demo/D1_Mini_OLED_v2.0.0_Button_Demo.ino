/*
 * 
 * Button Demo for the version 2.0 OLED shield with 2 buttons.
 * Usage - Hit a button, see the button name on the screen.
 * Example By LeRoy Miller (C) 2018
 * If you find this or any of my projects useful or enjoyable please support me.  
Anything I do get goes to buy more parts and make more/better projects.  
https://www.patreon.com/kd8bxp  
https://ko-fi.com/lfmiller 
https://www.youtube.com/channel/UCP6Vh4hfyJF288MTaRAF36w  
https://kd8bxp.blogspot.com/  

Required Library: Adafruit_D1_SSD1306 which is a slightly modified version
of mcauser's Adafruit SSD1306 library for the D1 Mini with 64x48 OLED screen
Mine is a renaming so that the Original Adafruit Library and 
MCAuser's library can live together.
https://github.com/kd8bxp/mcauser-64x48-OLED-SSD1306-library

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses>
 */
 

#include <Wire.h>
#include <Adafruit_D1_SSD1306.h>

#define OLED_RESET 0
Adafruit_D1_SSD1306 display(OLED_RESET);

#define BPIN D4
#define APIN D3

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  

  // Clear the buffer.
  display.clearDisplay();
  display.display();
 pinMode(BPIN, INPUT_PULLUP); //B
 pinMode(APIN, INPUT_PULLUP); //A
 attachInterrupt(digitalPinToInterrupt(BPIN), displayB, HIGH);
 attachInterrupt(digitalPinToInterrupt(APIN), displayA, HIGH);
}

void loop() {
  
}

void displayB() {
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("B");
  display.display();
  
}

void displayA() {
  display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(10,10);
  display.println("A");
  display.display();
  
}

