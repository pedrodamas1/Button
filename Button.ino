#include "src/Button.h"

Button myBtn(8);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myBtn.setTimes(500, 100);
}

void loop() {
  // put your main code here, to run repeatedly:
  myBtn.loop();
  if ( myBtn.wasPressed() ) {
    Serial.println( "You pressed the button" );  
  }
}
