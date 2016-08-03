/*
 * Scan I2C bus for devices.
 * Outputs a table similar to the i2cdetect linux program.
 *
 * Connect a device to the I2C bus and it will appear in the table.
 * D1 = SCL
 * D2 = SDA
 *
 * Dependencies:
 * https://github.com/mcauser/i2cdetect
 */

#include <Wire.h>
#include <i2cdetect.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("i2cdetect\n");
  Serial.print("Scanning...\n\n");
}

void loop() {
  //eg. i2cdetect(from=0x03, to=0x77);
  i2cdetect();  // default range from 0x03 to 0x77
  delay(2000);
}
