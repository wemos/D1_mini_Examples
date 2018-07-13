/*
 * Micro SD Shield - Datalogger
 *
 * This example shows how to log data from an analog sensor
 * to an SD card using the SD library.
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
 * The WeMos D1 Mini has one analog pin A0.
 *
 * The SD card library uses 8.3 format filenames and is case-insensitive.
 * eg. IMAGE.JPG is the same as image.jpg
 *
 * created  24 Nov 2010
 * modified 9 Apr 2012 by Tom Igoe
 *
 * This example code is in the public domain.
 * https://github.com/esp8266/Arduino/blob/master/libraries/SD/examples/Datalogger/Datalogger.ino
 */

#include <SPI.h>
#include <SD.h>

// change this to match your SD shield or module;
// WeMos Micro SD Shield V1.0.0: D8
// LOLIN Micro SD Shield V1.2.0: D4 (Default)
const int chipSelect = D4;

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
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";

  // read three sensors and append to the string:
  //for (int analogPin = 0; analogPin < 3; analogPin++) {
  //  int sensor = analogRead(analogPin);
  //  dataString += String(sensor);
  //  if (analogPin < 2) {
  //    dataString += ",";
  //  }
  //}
  // The WeMos D1 Mini only has one analog pin A0.
  int sensor = analogRead(A0);
  dataString += String(sensor);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }

  delay(1000);
}
