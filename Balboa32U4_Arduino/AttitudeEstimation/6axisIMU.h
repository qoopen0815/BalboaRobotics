#pragma once

#include <LSM6.h>

LSM6 imu;

float gx, gy, gz, ax, ay, az;

void setupLSM6(void)
{
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
  // Set the gyro full scale to 500 dps
  imu.writeReg(LSM6::CTRL2_G, 0b10000100);
  // Set the accelerometer full scale to 8 g
  imu.writeReg(LSM6::CTRL1_XL, 0b10001111);
  imu.calibrateIMU();
}

void setup6IMU(void)
{
  setupLSM6();
}

void update6IMU(void)
{
    imu.read();
  
    // 加速度値を分解能で割って加速度(G)に変換する
    ax = imu.a.x / 0.244;  // FS_XL 8 g => 4,096 LSB/g [0.244 mg/LSB]
    ay = imu.a.y / 0.244;
    az = imu.a.z / 0.244;
  
    // 角速度値を分解能で割って角速度(degrees per sec)に変換する
    gx = (imu.g.x-imu.cg.x) / 17.5;  // FS_G 500 dps => 57.1 LSB/dps [17.50 mdps/LSB]
    gy = (imu.g.y-imu.cg.y) / 17.5;
    gz = (imu.g.z-imu.cg.z) / 17.5;
}
