/* Conway's Game of Life
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 * The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells,
 * each of which is in one of two possible states, alive or dead.
 *
 * Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically,
 * or diagonally adjacent.
 *
 * At each step in time, the following transitions occur:
 *   1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 *   2. Any live cell with two or three live neighbours lives on to the next generation.
 *   3. Any live cell with more than three live neighbours dies, as if by over-population.
 *   4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * Connections:
 * WeMos D1 Mini   Nokia 5110    Description
 * (ESP8266)       PCD8544 LCD
 *
 * D2 (GPIO4)      0 RST         Output from ESP to reset display
 * D1 (GPIO5)      1 CE          Output from ESP to chip select/enable display
 * D6 (GPIO12)     2 DC          Output from display data/command to ESP
 * D7 (GPIO13)     3 Din         Output from ESP SPI MOSI to display data input
 * D5 (GPIO14)     4 Clk         Output from ESP SPI clock
 * 3V3             5 Vcc         3.3V from ESP to display
 * D0 (GPIO16)     6 BL          3.3V to turn backlight on, or PWM
 * G               7 Gnd         Ground
 *
 * More info:
 * https://github.com/mcauser/WeMos-D1-mini-Nokia-5110-PCD8544
 *
 * Dependencies:
 * https://github.com/adafruit/Adafruit-GFX-Library
 * https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
 * - This pull request adds ESP8266 support:
 * - https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/pull/27
 */

#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Pins
const int8_t RST_PIN = D2;
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;
//const int8_t DIN_PIN = D7;  // Uncomment for Software SPI
//const int8_t CLK_PIN = D5;  // Uncomment for Software SPI
const int8_t BL_PIN = D0;

#define PIXEL_SIZE 4  // Big pixels
#define SPEED 20      // Delay in ms between generations

// Software SPI with explicit CE pin.
// Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);

// Software SPI with CE tied to ground. Saves a pin but other pins can't be shared with other hardware.
// Adafruit_PCD8544(int8_t CLK_PIN, int8_t DIN_PIN, int8_t DC_PIN, int8_t RST_PIN);

// Hardware SPI based on hardware controlled SCK (SCLK) and MOSI (DIN) pins. CE is still controlled by any IO pin.
// NOTE: MISO and SS will be set as an input and output respectively, so be careful sharing those pins!
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("\n\nWeMos D1 Mini + Nokia 5110 PCD8544 84x48 Monochrome LCD\nUsing Adafruit_PCD8544 and Adafruit_GFX libraries\n");

  // Turn LCD backlight on
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  display.begin();
  display.setContrast(60);  // Adjust for your display
  Serial.println("Show Adafruit logo bitmap");

  // Show the Adafruit logo, which is preloaded into the buffer by their library
  // display.clearDisplay();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.println("Conway's");
  display.println("Game of Life");
  display.display();
  delay(2000);
}

void loop() {
  // Random Seed
  display.clearDisplay();
  randomise();
  display.display();
  delay(1000);

  // Begin
  int generations = 0;
  while(tick()) {
    generations++;
    display.display();
    delay(SPEED);
  }

  // Finish
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0,0);
  display.println(generations);
  display.display();

  // Restart
  delay(5000);
}

void randomise() {
  for (uint8_t x = 0; x < LCDWIDTH; x = x + PIXEL_SIZE) {
    for (uint8_t y = 0; y < LCDHEIGHT; y = y + PIXEL_SIZE) {
      cell(x, y, random(0,2));  // 0 = White, 1 = Black
    }
  }
}

void cell(int x, int y, int color) {
  for (uint8_t i = 0; i < PIXEL_SIZE; i++) {
    for (uint8_t j = 0; j < PIXEL_SIZE; j++) {
      display.drawPixel(x + i, y + j, color);
    }
  }
}

bool tick() {
  bool something_happened = false;
  for (uint8_t x = 0; x < LCDWIDTH; x = x + PIXEL_SIZE) {
    for (uint8_t y = 0; y < LCDHEIGHT; y = y + PIXEL_SIZE) {

      // The current cell
      uint8_t alive = display.getPixel(x, y);

      // Count number of neighbours
      uint8_t neighbours = (
        display.getPixel(x - PIXEL_SIZE, y - PIXEL_SIZE) +
        display.getPixel(x, y - PIXEL_SIZE) +
        display.getPixel(x + PIXEL_SIZE, y - PIXEL_SIZE) +
        display.getPixel(x - PIXEL_SIZE, y) +
        display.getPixel(x + PIXEL_SIZE, y) +
        display.getPixel(x + PIXEL_SIZE, y + PIXEL_SIZE) +
        display.getPixel(x, y + PIXEL_SIZE) +
        display.getPixel(x - PIXEL_SIZE, y + PIXEL_SIZE)
      );

      // Apply the rules of life
      if (alive && (neighbours < 2 || neighbours > 3)) {
        cell(x, y, WHITE); // death
        if (!something_happened) something_happened = true;
      }
      else if (!alive && neighbours == 3) {
        cell(x, y, BLACK); // birth
        if (!something_happened) something_happened = true;
      }
    }
  }

  return something_happened;
}
