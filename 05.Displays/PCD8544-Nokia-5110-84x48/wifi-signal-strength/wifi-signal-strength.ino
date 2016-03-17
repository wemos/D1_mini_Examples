/* WiFi Signal Strength
 * Shows RSSI of a predefined network with a graph
 *
 * RSSI is a percentage in the range -120db to 0db.
 * The closer to 0 the better.
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
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

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

// Graph the RSSI of this WiFi
const char* myssid = "YOUR WIFI SSID";
const char* mypass = "YOUR WIFI PASSWORD";

long rssi;
int8_t graph[83];
uint8_t i, col, pos = 0;
bool scroll = false;

// Software SPI with explicit CS pin.
//Adafruit_PCD8544(int8_t CLK_PIN, int8_t DIN_PIN, int8_t DC_PIN, int8_t CE_PIN, int8_t RST_PIN);

// Software SPI with CS tied to ground.  Saves a pin but other pins can't be shared with other hardware.
//Adafruit_PCD8544(int8_t CLK_PIN, int8_t DIN_PIN, int8_t DC_PIN, int8_t RST_PIN);

// Hardware SPI based on hardware controlled SCK (SCLK) and MOSI (DIN) pins. CS is still controlled by any IO pin.
// NOTE: MISO and SS will be set as an input and output respectively, so be careful sharing those pins!
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

void setup(void) {
  Serial.begin(9600);
  Serial.println("\nESP8266 WiFi Signal Strength Graph");
  Serial.println("WeMos D1 Mini + Nokia 5110 PCD8544 84x48 Monochrome LCD\nUsing Adafruit_PCD8544 and Adafruit_GFX libraries\n");

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Turn LCD backlight on
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  // Configure LCD
  display.begin();
  display.setContrast(60);  // Adjust for your display
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.clearDisplay();

  WiFi.begin(myssid, mypass);
  Serial.print("Connecting");
  display.print("Connecting");
  display.display();

  // Wait for successful connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    display.print(".");
    display.display();
  }

  Serial.print("\nConnected to: ");
  Serial.println(myssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  display.clearDisplay();
  display.println("Connected");
  display.display();
  delay(1000);
}

void loop(void) {
  rssi = WiFi.RSSI();  // eg. -63

  // Convert to scale -48 to 0 eg. map(rssi, -100, 0, 0, -48);
  // I used -100 instead of -120 because <= -95 is unusable
  // Negative number so we can draw n pixels from the bottom in black
  graph[pos] = (1.0 - (rssi / -100.0)) * -48.0;

  // Draw the RSSI eg. -63db
  display.clearDisplay();
  display.printf("%ddb\n",rssi);

  // Draw the graph left to right until 84 columns visible
  // After that shuffle the graph to the left and update the right most column
  if (!scroll) {
    for (i = 0; i <= pos; i++) {
      display.drawFastVLine(i, LCDHEIGHT-1, graph[i], BLACK);
    }
  }
  else {
    for (i = 0; i < LCDWIDTH; i++) {
      col = (i + pos + 1) % LCDWIDTH;
      display.drawFastVLine(i, LCDHEIGHT-1, graph[col], BLACK);
    }
  }
  display.display();

  // After the first pass, scroll the graph to the left
  if (pos == 83) {
    pos = 0;
    scroll = true;
  }
  else {
    pos++;
  }

  delay(100);  // Adjust this to change graph speed
}
