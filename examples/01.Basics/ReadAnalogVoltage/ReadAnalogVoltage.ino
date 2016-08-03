/*
  ReadAnalogVoltage
  The ESP8266EX(Which IC D1 board used)  integrates a generic purpose 10-bit analog ADC. The ADC range is from 0V to 1.0V
  And on the  board, we use following circuit:

  -----A0
  |
 220K
  |--- ADC
 100K
  |
 GND

so,the input voltage(A0) can be 3.2V, and the A0=3.2*ADC

 */

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 3.2V):
  float voltage = sensorValue * (3.2 / 1023.0);
  // print out the value you read:
  Serial.println(voltage);
}
