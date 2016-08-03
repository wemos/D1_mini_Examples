/*
 * 1 Button Shield - Simple Push
 * Press the pushbutton to switch on the LED
 *
 * 1 Button Shield pushbutton connects pin D3 to GND
 */

const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial state, LED off
  digitalWrite(ledPin, buttonState);
}

void loop() {
  // read button state, HIGH when pressed, LOW when not
  buttonState = digitalRead(buttonPin);

  // if the push button pressed, switch on the LED
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);  // LED on
  } else {
    digitalWrite(ledPin, LOW); // LED off
  }
}
