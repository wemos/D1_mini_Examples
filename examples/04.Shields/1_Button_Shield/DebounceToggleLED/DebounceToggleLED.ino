/*
 * 1 Button Shield - Debounce Toggle LED
 * Press the pushbutton to toggle the LED
 *
 * Pushbuttons often generate spurious open/close transitions when pressed, due to mechanical and physical issues.
 * This example demonstrates how to debounce an input, which means checking twice in a short period of time to make sure the pushbutton is definitely pressed.
 *
 * 1 Button Shield pushbutton connects pin D3 to GND
 */

const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

// the current state of the LED and button
int ledState = LOW;
int buttonState = LOW;

// the current and previous readings from the input pin
int thisButtonState = LOW;
int lastButtonState = LOW;

// time is measured in milliseconds and will quickly exceed limitations of an integer, so we use a long for these two
unsigned long lastDebounceTime = 0;  // the time the button state last switched
unsigned long debounceDelay = 50;    // the state must remain the same for this many millis to register the button press

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // the buttonPin is read multiple times and the value must remain the same for debounceDelay millis to toggle the LED

  // read button state, HIGH when pressed, LOW when not
  thisButtonState = digitalRead(buttonPin);

  // if the current state does not match the previous state
  // the button was just pressed/released, or is transition noise
  if (thisButtonState != lastButtonState) {
    // reset the timer
    lastDebounceTime = millis();
  }

  // once delay millis have elapsed, if the state remains the same, register the press
  if ((millis() - lastDebounceTime) > debounceDelay) {

    // if the button state has changed
    if (thisButtonState != buttonState) {
      buttonState = thisButtonState;

      // only toggle the LED if the buttonState has switched from LOW to HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        // toggle the LED
        digitalWrite(ledPin, ledState);
      }
    }
  }

  // persist for next loop iteration
  lastButtonState = thisButtonState;
}
