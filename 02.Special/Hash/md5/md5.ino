/**
 * Simple demo to show md5 calculation
 *
 * https://github.com/esp8266/Arduino/blob/master/cores/esp8266/md5.h
 */

#include <MD5Builder.h>

MD5Builder _md5;

String md5(String str) {
  _md5.begin();
  _md5.add(String(str));
  _md5.calculate();
  return _md5.toString();
}

void setup() {
  Serial.begin(9600);

  Serial.println("MD5 example\n");

  Serial.println("MD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8 (known)");
  Serial.print("MD5 (\"foo\") = ");
  Serial.print(md5("foo"));
  Serial.println(" (calculated)\n");

  Serial.println("MD5 (\"bar\") = 37b51d194a7513e45b56f6524f2d51f2 (known)");
  Serial.print("MD5 (\"bar\") = ");
  Serial.print(md5("bar"));
  Serial.println(" (calculated)\n");

  Serial.println("MD5 (\"wemos d1 mini\") = c4594198428b13c196b05161d3e9c86e (known)");
  Serial.print("MD5 (\"wemos d1 mini\") = ");
  Serial.print(md5("wemos d1 mini"));
  Serial.println(" (calculated)\n");
}

void loop() {
}
