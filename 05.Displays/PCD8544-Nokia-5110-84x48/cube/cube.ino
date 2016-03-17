/* Rotating 3D cube
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


// Software SPI with explicit CE pin.
// Adafruit_PCD8544 display = Adafruit_PCD8544(CLK_PIN, DIN_PIN, DC_PIN, CE_PIN, RST_PIN);

// Software SPI with CE tied to ground. Saves a pin but other pins can't be shared with other hardware.
// Adafruit_PCD8544(int8_t CLK_PIN, int8_t DIN_PIN, int8_t DC_PIN, int8_t RST_PIN);

// Hardware SPI based on hardware controlled SCK (SCLK) and MOSI (DIN) pins. CE is still controlled by any IO pin.
// NOTE: MISO and SS will be set as an input and output respectively, so be careful sharing those pins!
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);


#define SHAPE_SIZE 700
#define ROTATION_SPEED 25 // Delay in ms between cube redraws

float d = 3;
float px[] = { -d,  d,  d, -d, -d,  d,  d, -d };
float py[] = { -d, -d,  d,  d, -d, -d,  d,  d };
float pz[] = { -d, -d, -d, -d,  d,  d,  d,  d };

float p2x[] = {0,0,0,0,0,0,0,0};
float p2y[] = {0,0,0,0,0,0,0,0};

float r[] = {0,0,0};

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
  display.display();
}

void loop() {
  drawCube();
  delay(ROTATION_SPEED);
}

void drawCube() {
  r[0] = r[0] + PI / 180.0; // Add a degree
  r[1] = r[1] + PI / 180.0; // Add a degree
  r[2] = r[2] + PI / 180.0; // Add a degree
  if (r[0] >= 360.0 * PI / 180.0) r[0] = 0;
  if (r[1] >= 360.0 * PI / 180.0) r[1] = 0;
  if (r[2] >= 360.0 * PI / 180.0) r[2] = 0;

  for (int i = 0; i < 8; i++) {
    float px2 = px[i];
    float py2 = cos(r[0]) * py[i] - sin(r[0]) * pz[i];
    float pz2 = sin(r[0]) * py[i] + cos(r[0]) * pz[i];

    float px3 = cos(r[1]) * px2 + sin(r[1]) * pz2;
    float py3 = py2;
    float pz3 = -sin(r[1]) * px2 + cos(r[1]) * pz2;

    float ax = cos(r[2]) * px3 - sin(r[2]) * py3;
    float ay = sin(r[2]) * px3 + cos(r[2]) * py3;
    float az = pz3 - 150;

    p2x[i] = LCDWIDTH / 2 + ax * SHAPE_SIZE / az;
    p2y[i] = LCDHEIGHT / 2 + ay * SHAPE_SIZE / az;
  }

  display.clearDisplay();

  for (int i = 0; i < 3; i++) {
    display.drawLine(p2x[i],   p2y[i],   p2x[i+1], p2y[i+1], BLACK);
    display.drawLine(p2x[i+4], p2y[i+4], p2x[i+5], p2y[i+5], BLACK);
    display.drawLine(p2x[i],   p2y[i],   p2x[i+4], p2y[i+4], BLACK);
  }

  display.drawLine(p2x[3], p2y[3], p2x[0], p2y[0], BLACK);
  display.drawLine(p2x[7], p2y[7], p2x[4], p2y[4], BLACK);
  display.drawLine(p2x[3], p2y[3], p2x[7], p2y[7], BLACK);

  display.display();
}
