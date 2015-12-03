/*
  Basic Ticker usage
  
  Ticker is an object that will call a given function with a certain period.
  Each Ticker calls one function. You can have as many Tickers as you like,
  memory being the only limitation.
  
  A function may be attached to a ticker and detached from the ticker.
  There are two variants of the attach function: attach and attach_ms.
  The first one takes period in seconds, the second one in milliseconds.
  
  An LED connected to D13 will be blinking. 
*/

#include <Ticker.h>

Ticker flipper;

int count = 0;

void flip()
{
  int state = digitalRead(D13);  // get the current state of GPIO1 pin
  digitalWrite(D13, !state);     // set pin to the opposite state
  
  ++count;
  // when the counter reaches a certain value, start blinking like crazy
  if (count == 20)
  {
    flipper.attach(0.1, flip);
  }
  // when the counter reaches yet another value, stop blinking
  else if (count == 120)
  {
    flipper.detach();
  }
}

void setup() {
  pinMode(D13, OUTPUT);
  digitalWrite(D13, LOW);
  
  // flip the pin every 0.3s
  flipper.attach(0.3, flip);
}

void loop() {
}
