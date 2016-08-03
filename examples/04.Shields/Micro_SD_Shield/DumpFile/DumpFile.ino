/*
 * Micro SD Shield - File dump
 *
 * This example shows how to read a file from the SD card using the
 * SD library and send it over the serial port.
 *
 * The WeMos Micro SD Shield uses:
 * D5, D6, D7, D8, 3V3 and G
 *
 * The shield uses SPI bus pins:
 * D5 = CLK
 * D6 = MISO
 * D7 = MOSI
 * D8 = CS
 *
 * The SD card library uses 8.3 format filenames and is case-insensitive.
 * eg. IMAGE.JPG is the same as image.jpg
 *
 * created  22 December 2010 by Limor Fried
 * modified 9 Apr 2012 by Tom Igoe
 *
 * This example code is in the public domain.
 * https://github.com/esp8266/Arduino/blob/master/libraries/SD/examples/DumpFile/DumpFile.ino
 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = D8;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void loop()
{
  // nothing happens after setup
}
