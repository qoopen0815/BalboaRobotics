/*
Balboa32U4 motor speed is limited from -300 to 300.
This program check an applied voltage to motor in case that a motor speed set on 300.
*/

#include <Balboa32U4.h>

Balboa32U4Motors motors;
Balboa32U4ButtonA buttonA;

void setup()
{
  // Wait for the user to press button A.
  buttonA.waitForButton();
}

void loop()
{
  int speed = 300;
  motors.setLeftSpeed(speed);
  motors.setRightSpeed(speed);
}
