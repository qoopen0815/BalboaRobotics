#include <Wire.h>
#include <Balboa32U4.h>
#include <LSM6.h>
#include <LIS3MDL.h>
#include <MadgwickAHRS.h>

#define Ts 10  //ms
#define kp 50
#define ki 0
#define kd 0
#define theta_r 0

LSM6 imu;
LIS3MDL mag;
Madgwick MF;
Balboa32U4Motors motors;

float error_sum;
float error_past;

void setupLIS3MDL(void)
{
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
  // Set the magnetic full scale to 8gauss
  mag.writeReg(LIS3MDL::CTRL_REG2, 0b00100000);
  mag.enableDefault();
}

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

void setup()
{
  Wire.begin();
  setupLIS3MDL();
  setupLSM6();
  Serial.begin(9600);
  MF.begin(50); //100Hz

  error_sum = 0;
  error_past = 0;
}

void loop()
{
  static uint8_t lastTime;

  if ((uint8_t)(millis() - lastTime) >= Ts)
  {
    lastTime = millis();
    
    imu.read();
    mag.read();
  
    // 加速度値を分解能で割って加速度(G)に変換する
    float ax = imu.a.x / 0.244;  // FS_XL 8 g => 4,096 LSB/g [0.244 mg/LSB]
    float ay = imu.a.y / 0.244;
    float az = imu.a.z / 0.244;
  
    // 角速度値を分解能で割って角速度(degrees per sec)に変換する
    float gx = (imu.g.x-imu.cg.x) / 17.5;  // FS_G 500 dps => 57.1 LSB/dps [17.50 mdps/LSB]
    float gy = (imu.g.y-imu.cg.y) / 17.5;
    float gz = (imu.g.z-imu.cg.z) / 17.5;
    
    // 地磁気値を分解能で割って磁力値(gauss)に変換する
    float mx = mag.m.x * 3421.0;  // FS 8 gauss => 3,421 LSB/gauss
    float my = mag.m.y * 3421.0;
    float mz = mag.m.z * 3421.0;
  
    MF.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    float PITCH = 0;

    if(az > 0)
    {
      PITCH = -90 - MF.getPitch();
    }
    else
    {
      PITCH = 90 + MF.getPitch();
    }

    float error = theta_r - PITCH;
    error_sum += error;
    // input
    float u = kp*error + ki*error_sum + kd*(error - error_past)/Ts; 
    error_past = error;
    
    motors.setLeftSpeed(u);
    motors.setRightSpeed(u);
  }
  
}
