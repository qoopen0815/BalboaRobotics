# Balboa32U4-arduino
Arduino code for [Balboa32U4](https://www.pololu.com/docs/0J70)

## Sensor
- [Attitude Estimation](https://github.com/calm0815/BalboaRobotics/tree/master/Balboa32U4/Arduino/AttitudeEstimation)  
    - [LSM6 (6DoF IMU)](https://github.com/pololu/lsm6-arduino)  
        I add new function, calibrateIMU(). Please download package from [lsm6-arduino](https://github.com/calm0815/lsm6-arduino)
    - [LIS3MDL (3DoF Magnetic Sensor)](https://github.com/pololu/lis3mdl-arduino)
    - [MadgwickAHRS](https://github.com/arduino-libraries/MadgwickAHRS)

## Inverted pendulum
- [identification](https://github.com/calm0815/BalboaRobotics/tree/master/Balboa32U4/Arduino/param_identification)
    - [applied_voltage](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4/Arduino/param_identification/applied_voltage/applied_voltage.ino)  
    指令値('setSpeeds()')が最大のときの電圧を調べるため

- [FeedbackController](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4/Arduino/FeedbackController/FeedbackController.ino)  
using observer

## Dependency
- [BasicLinearAlgebra](https://github.com/tomstewart89/BasicLinearAlgebra)
- [StateSpaceControl](https://github.com/tomstewart89/StateSpaceControl)
