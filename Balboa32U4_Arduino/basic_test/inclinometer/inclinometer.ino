#include <Wire.h>
#include <Balboa32U4.h>
#include <LSM6.h>
#include <LIS3MDL.h>
#include <TimerThree.h>

LSM6 imu;
LIS3MDL mag;
Balboa32U4Buzzer buzzer;

void timerFire() {
  //100ms（=100000us）毎にここが呼び出される
  imu.read();
  mag.read();

  Serial.println(imu.a.x);
  
  // Start playing a tone with frequency 440 Hz at maximum
  // volume (15) for 200 milliseconds.
  buzzer.playFrequency(440, 200, 10);

  // Delay to give the tone time to finish.
  delay(10);
}

void setup()
{
  Timer3.initialize(10000000); //マイクロ秒単位で設定
  Timer3.attachInterrupt(timerFire);
  
  Wire.begin();

  if (!mag.init())
  {
    // Failed to detect the LIS3MDL.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to detect the LIS3MDL."));
      delay(100);
    }
  }

  mag.enableDefault();

  if (!imu.init())
  {
    // Failed to detect the LSM6.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to detect the LSM6."));
      delay(100);
    }
  }

  imu.enableDefault();

  // Set the gyro full scale to 1000 dps because the default
  // value is too low, and leave the other settings the same.
  imu.writeReg(LSM6::CTRL2_G, 0b10001000);

  // Set the accelerometer full scale to 16 g because the default
  // value is too low, and leave the other settings the same.
  imu.writeReg(LSM6::CTRL1_XL, 0b10000100);
}

void loop()
{
  imu.read();
  mag.read();

  delay(100);
}
