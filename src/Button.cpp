
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


#include <Arduino.h>
#include "Button.h"


// Basic constructor for creating class instance.
Button::Button() {}


// Constructor that creates instance and define switch pin.
Button::Button( uint8_t SW ) : switchPin(SW)
{
	pinMode( switchPin, INPUT_PULLUP );
}


// Destructor, to wrap up at the end.
Button::~Button() {}


// Alternative to the constructor for setting up the pin.
void Button::setup(uint8_t SW)
{
	switchPin = SW;
	pinMode( switchPin, INPUT_PULLUP );
}


// Main loop for the button
void Button::loop()
{
	// Is the button being pressed this very moment??
	if ( isPressed_() ) {

		wasFirstPress_();
		hasActivated_();
	}

	else if ( !isPressed_() )  {
		isFirstPress = true;
	}

	hasTimedOut_();

}


// Checks if the button was pressed.
bool Button::wasPressed()
{
	if (pressed) {
		pressed = false;
		return true;
	}
	else {
		return false;
	}
}


// Sets the activation and timeout times.
bool Button::setTimes(
	unsigned long activation = 1000, 
	unsigned long timeout = 100)
{
	this -> activation = activation;
	this -> timeout = timeout;
}


// Returns the intuitive button state
bool Button::isPressed_()
{
	return !digitalRead(switchPin);
}


// Checks if the button activated successfully
void Button::hasActivated_()
{
	// Have we exceed the activation time??
	if (millis() - actTime > activation) {
		// If we have, then the button was successfully activated!
		pressed = true;
		// Start counting the timeout
		toTime = millis();
		isFirstPress = true;
	}
}


// Checks if the button has timed-out or not
void Button::hasTimedOut_()
{
	if ( pressed ) {
		// If the button was pressed, then there's a time limit for it
		if ( millis() - toTime > timeout ) {
			// timeout!
			pressed = false;
		}
	}
}


// Checks if it was the first press
void Button::wasFirstPress_()
{
	// Okay, but was it pressed JUST now?
	if ( isFirstPress ) {
		// If this was the first reading of that click,
		// then the next reading will not be the first anymore
		isFirstPress = false;
		// Start counting the activation time
		actTime = millis();
	}
}