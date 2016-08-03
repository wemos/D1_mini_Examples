/*
 * IO test
 * 
 *
 * 
 */

int pins[9]={D0,D1,D2,D3,D4,D5,D6,D7,D8};


void setup() {
  
	for(int i=0;i<9;i++)
	{
		pinMode(pins[i],OUTPUT);
		digitalWrite(pins[i],0);
	}
}

void loop() {
  
	for(int i=0;i<9;i++)
	{
		digitalWrite(pins[i],1);
		delay(10);
		digitalWrite(pins[i],0);
		delay(10);
	}
 delay(1000);
}
