
/*
	Button.h

	Library for interfacing with a standard push button.
	The library has two special features:
		1 - an activation time, only after which a push is reported
		2 - a timeout time, after which that detection "expires"

	The circuit:
	* Button GND pin to ground
	* Button DT pin to digital pin 8

	Created June 8, 2020
	By Pedro M. Damas
	Modified June 8, 2020
	By Pedro M. Damas

	Released into the public domain.

	https://github.com/pedrodamas1/Button
*/


// Must define the virtual delay time and the timeout duration


// Include guard
#ifndef Button_h
#define Button_h


// Class definition
class Button {

	// Pin on the button
	uint8_t switchPin;

	// Booleans for the first press reading and the successful click
	bool isFirstPress = true;
	bool pressed = false;
	
	// Activation and timeout start times
	unsigned long actTime = 0; 
	unsigned long toTime = 0;

	// Timeout and activation times
	unsigned long timeout;
	unsigned long activation;


public:

	// Overloaded constructor
	Button();
	Button(uint8_t SW);

	// Destructor
	~Button();

	// Alternative to the constructor for setting up the pin.
	void setup(uint8_t SW);
	// Main loop for the button.
	void loop();
	// Checks if the button was pressed.
	bool wasPressed();
	// Sets the activation and timeout times.
	bool setTimes(unsigned long activation, unsigned long timeout);


private:

	// Returns the intuitive button state
	bool isPressed_();
	// Checks if the button activated successfully
	void hasActivated_();
	// Checks if the button has timed-out or not
	void hasTimedOut_();
	// Checks if it was the first press
	void wasFirstPress_();

};


#endif