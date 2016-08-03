/*
 * Relay Shield - Blink Without Delay
 * Turns on the relay for two seconds, then off for two seconds, repeatedly.
 * This uses millis() instead of delay() to avoid blocking.
 *
 * Relay Shield transistor closes relay when D1 is HIGH
 */

const int relayPin = D1;
const long interval = 2000;  // pause for two seconds

int relayState = LOW;
unsigned long previousMillis = 0;


void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  // if enough millis have elapsed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // toggle the relay
    relayState = !relayState;
    digitalWrite(relayPin, relayState);
  }
}
