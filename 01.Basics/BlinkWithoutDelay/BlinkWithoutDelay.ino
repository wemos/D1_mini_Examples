/*
 * Blink Without Delay
 * Turns on the onboard LED on for one second, then off for one second, repeatedly.
 * This uses millis() instead of delay() to avoid blocking.
 */

const long interval = 1000;

int ledState = LOW;
unsigned long previousMillis = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output
}

void loop() {
  unsigned long currentMillis = millis();

  // if enough millis have elapsed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // toggle the LED
    ledState = !ledState;
    digitalWrite(BUILTIN_LED, ledState);
  }
}
