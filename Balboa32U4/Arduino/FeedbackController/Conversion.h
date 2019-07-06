#define PI 3.14159

//convert encoder val to wheel deg
float en2deg(float encoder)
{
  /*
  「1321.236」は車輪を１回転させたときのエンコーダの値
  - モータギア比　50:1 (正確には51.45:1)
  - シャーシ側ギア比　45:21 (2.14:1 reduction)
  - エンコーダカウント数 12 (1回転)
  以上より、51.45*2.14*12 = 1321.236
  */
  return encoder * 360/1321.236;
}

//convert deg to rad
float deg2rad(float deg)
{
  float rad = deg * PI/180;
  
  return rad;
}

//convert rad to deg
float rad2deg(float rad)
{
  float deg = rad * 180/PI;
  
  return deg;
}
