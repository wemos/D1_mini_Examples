/*
Basic IO
 */

int inPin = D3;   // pushbutton connected to digital pin D3
int val = 0;     // variable to store the read value

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);      // 
  pinMode(inPin, INPUT);      // sets pin as input
}

void loop()
{
  val = digitalRead(inPin);   // read the input pin
  digitalWrite(BUILTIN_LED, val);    // sets the LED to the button's value
}