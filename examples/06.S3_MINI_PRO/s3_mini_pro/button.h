#ifndef button_h
#define button_h

#include <FunctionalInterrupt.h>

class Button{
public:
  Button(uint8_t reqPin) : PIN(reqPin){
    pinMode(PIN, INPUT_PULLUP);
  };

  void begin(){
    attachInterrupt(PIN, std::bind(&Button::isr,this), FALLING);
    Serial.printf("Started button interrupt on pin %d\n", PIN);
  }

  ~Button(){
    detachInterrupt(PIN);
  }

	void ARDUINO_ISR_ATTR isr() {

		if ((millis() - lastDebounceTime) > debounceDelay) {
      pressed = true;
    }

    lastDebounceTime = millis();
	}

	bool checkPressed() {
		if (pressed) {
      
			// Serial.printf("Button on pin %u has been pressed %lu times\n", PIN, numberKeyPresses);
			pressed = false;
      return true;
		}else{
      return false;
    }
	}

private:
    const uint8_t PIN;
    volatile bool pressed;
    volatile unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
    unsigned long debounceDelay = 300;    // the debounce time; increase if the output flickers

};

#endif