/*
  Passing paramters to Ticker callbacks
  
  Apart from void(void) functions, the Ticker library supports 
  functions taking one argument. This argument's size has to be less or
  equal to 4 bytes (so char, short, int, float, void*, char* types will do).
  
  This sample runs two tickers that both call one callback function,
  but with different arguments.

  An LED connected to D13 will be pulsing. 
*/

#include <Ticker.h>

Ticker tickerSetHigh;
Ticker tickerSetLow;

void setPin(int state) {
  digitalWrite(D13, state);
}

void setup() {
  pinMode(D13, OUTPUT);
  digitalWrite(D13, LOW);
  
  // every 25 ms, call setPin(0) 
  tickerSetLow.attach_ms(25, setPin, 0);
  
  // every 26 ms, call setPin(D13)
  tickerSetHigh.attach_ms(26, setPin, 1);
}

void loop() {
}
