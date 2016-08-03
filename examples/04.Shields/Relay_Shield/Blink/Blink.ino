/*
 * Relay Shield - Blink
 * Turns on the relay for two seconds, then off for two seconds, repeatedly.
 *
 * Relay Shield transistor closes relay when D1 is HIGH
 */

const int relayPin = D1;
const long interval = 2000;  // pause for two seconds

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, HIGH); // turn on relay with voltage HIGH
  delay(interval);              // pause
  digitalWrite(relayPin, LOW);  // turn off relay with voltage LOW
  delay(interval);              // pause
}
