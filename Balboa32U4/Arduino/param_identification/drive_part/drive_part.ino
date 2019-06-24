#include <Balboa32U4.h>

#define Ts 1  //ms
#define phi_c 180 //deg
#define kp 5

Balboa32U4Encoders encoders;
Balboa32U4Motors motors;
Balboa32U4ButtonA buttonA;

int start;

void setup() 
{  
  // Wait for the user to press button A.
  buttonA.waitForButton();
  start = millis();
  Serial.begin(9600);
}

void loop() 
{
  static uint8_t lastDisplayTime;

  if ((uint8_t)(millis() - lastDisplayTime) >= Ts)
  {
    lastDisplayTime = millis();

    double phi = encoders.getCountsLeft();
    motors.setLeftSpeed(kp*(phi_c - phi*360/1321.236)); //up to 300 (param leftSpeed A number from -300 to 300)
   /*
    「1321.236」は車輪を１回転させたときのエンコーダの値
    - モータギア比　50:1 (正確には51.45:1)
    - シャーシ側ギア比　45:21 (2.14:1 reduction)
    - エンコーダカウント数 12 (1回転)
    以上より、51.45*2.14*12 = 1321.236
   */

    Serial.print(millis()-start);
    Serial.print("\t");
    Serial.print(phi*360/1324);
    Serial.print("\t");
    Serial.println(phi_c);
  }

}
