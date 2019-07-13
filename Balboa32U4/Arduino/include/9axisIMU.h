#pragma once
#include <LSM6.h>
#include <LIS3MDL.h>

LSM6 imu;
LIS3MDL mag;

float gx, gy, gz;
float ax, ay, az;
float mx, my, mz;

void setupLIS3MDL(void);

void setupLSM6(void);

void setupIMU(void);

void updateIMU(void);