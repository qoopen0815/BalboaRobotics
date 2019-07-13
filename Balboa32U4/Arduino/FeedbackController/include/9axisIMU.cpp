#include "9axisIMU.h"

void setupLIS3MDL(void)
{
    if (!mag.init())
    {
        // Failed to detect the LIS3MDL.
        // ledRed(1);
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
        // ledRed(1);
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

void setupIMU(void)
{
    setupLIS3MDL();
    setupLSM6();
}

void updateIMU(void)
{
    imu.read();
    mag.read();

    // 加速度値を分解能で割って加速度(G)に変換する
    ax = imu.a.x / 0.244;  // FS_XL 8 g => 4,096 LSB/g [0.244 mg/LSB]
    ay = imu.a.y / 0.244;
    az = imu.a.z / 0.244;

    // 角速度値を分解能で割って角速度(degrees per sec)に変換する
    gx = (imu.g.x-imu.cg.x) / 17.5;  // FS_G 500 dps => 57.1 LSB/dps [17.50 mdps/LSB]
    gy = (imu.g.y-imu.cg.y) / 17.5;
    gz = (imu.g.z-imu.cg.z) / 17.5;
    
    // 地磁気値を分解能で割って磁力値(gauss)に変換する
    mx = mag.m.x * 3421.0;  // FS 8 gauss => 3,421 LSB/gauss
    my = mag.m.y * 3421.0;
    mz = mag.m.z * 3421.0;
}
