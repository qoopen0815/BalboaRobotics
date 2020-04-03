#include <Wire.h>
#include <Balboa32U4.h>
#include "Conversion.h"
#include "6axisIMU.h"
#include "Kalman.h"

#define Ts 10.0  //周期Ts [ms]

static unsigned long startTime = 0;
static unsigned long goalTime = 0;
static unsigned long processTime = 0;

void setup()
{
  Serial1.begin(9600);
  Wire.begin();
  setup6IMU();
  setupKF();
}
  
void loop()
{
  startTime = millis();

  update6IMU();
  Serial1.println(theta_data[0][0]);

  goalTime = millis();
  delay(Ts - (goalTime - startTime));
}
