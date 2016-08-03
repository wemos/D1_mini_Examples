/*
 * Hello World
 * Simply prints Hello World to the serial monitor.
 */

void setup() {
  // initialize serial communications at 9600 bps
  Serial.begin(9600);
}

void loop() {
  Serial.println("Hello World.");
  delay(2000);
}
