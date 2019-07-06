#include <Wire.h>
#include <Balboa32U4.h>
#include "Conversion.h"

#define Ts 10.0  //周期Ts [ms]
#define Voffset 0.3768  //オフセット電圧 [V]

Balboa32U4Encoders encoders;
Balboa32U4Motors motors;

float phi_p, phi_w, phi_p_dot, phi_w_dot;
float phi_w_old, inputVal, inputVal_old;

static unsigned long startTime = 0;
static unsigned long goalTime = 0;
static unsigned long processTime = 0;

int input(float phi_p, float phi_p_dot, float phi_w, float phi_w_dot)
{
  float K[4] = {7.6344,  1.2947,  0.2309, 0.7571};
  float X[4] = {phi_p, phi_p_dot, phi_w, phi_w_dot};

  float u = (K[0] * X[0] + K[1] * X[1] + K[2] * X[2] + K[3] * X[3]);
  /*
    状態フィードバックコントローラ
    u = K * x
  */

  u += Voffset * u / abs(u);

  return u * 300.0 / 5.5;
}

void setup()
{
  Serial.begin(38400);
  Wire.begin();
  setupIMU();
}

void loop()
{
  startTime = millis();

  /* ------------ 状態変数更新(n)------------ */
  //  updateMadgwick();
  phi_w = en2deg(encoders.getCountsLeft());

  /* ------------ 変数整理 ------------ */

  /* ------ 姿勢推定 ------ */
  phi_p = (90.0 + MF.getPitch()) * az / abs(az);
  phi_p_dot = gy;

  /* ------ エンコーダ ------ */
  phi_w_dot = (phi_w - phi_w_old) * 1000.0 / Ts;

  /* ------------ 入力値算出 ------------ */
  inputVal = input(deg2rad(phi_p), deg2rad(phi_p_dot), deg2rad(phi_w), deg2rad(phi_w_dot));
  motors.setLeftSpeed((inputVal + inputVal_old) / 2.0);
  motors.setRightSpeed((inputVal + inputVal_old) / 2.0);
  inputVal_old = inputVal;

  /* ------------ 状態変数更新(n-1)------------ */
  phi_w_old = phi_w;

  //  Serial.print(inputVal);
  //  Serial.print("\t");
  //  Serial.println((inputVal + inputVal_old) / 2.0);

  goalTime = millis();
  delay(Ts - (goalTime - startTime));
}
