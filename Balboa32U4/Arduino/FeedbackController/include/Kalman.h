#pragma once

#include <TimerThree.h>
#include "9axisIMU.h"

//=========================================================
//Accelerometer and gyro statistical data
//=========================================================
int sample_num = 100;
float meas_interval = 0.01;
float theta_mean;
float theta_variance;
float theta_dot_mean;
float theta_dot_variance;

//=========================================================
//Kalman filter (for angle estimation) variables
//=========================================================
//Update rate
float theta_update_freq = 400; //Hz
float theta_update_interval = 1.0 / double(theta_update_freq);
//State vector
//[[theta(degree)], [offset of theta_dot(degree/sec)]]
float theta_data_predict[2][1];
float theta_data[2][1];
//Covariance matrix
float P_theta_predict[2][2];
float P_theta[2][2];
//"A" of the state equation
float A_theta[2][2] = {{1, -theta_update_interval}, {0, 1}};
//"B" of the state equation
float B_theta[2][1] = {{theta_update_interval}, {0}};
//"C" of the state equation
float C_theta[1][2] = {{1, 0}};

//=========================================================
// Matrix common functions
//=========================================================
//Matrix addition
void mat_add(float *m1, float *m2, float *sol, int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      sol[i * column + j] = m1[i * column + j] + m2[i * column + j];
    }
  }
  return;
}

//Matrix subtraction
void mat_sub(float *m1, float *m2, float *sol, int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      sol[i * column + j] = m1[i * column + j] - m2[i * column + j];
    }
  }
  return;
}

//Matrix multiplication
void mat_mul(float *m1, float *m2, float *sol, int row1, int column1, int row2, int column2)
{
  for (int i = 0; i < row1; i++)
  {
    for (int j = 0; j < column2; j++)
    {
      sol[i * column2 + j] = 0;
      for (int k = 0; k < column1; k++)
      {
        sol[i * column2 + j] += m1[i * column1 + k] * m2[k * column2 + j];
      }
    }
  }
  return;
}

//Matrix transposition
void mat_tran(float *m1, float *sol, int row_original, int column_original)
{
  for (int i = 0; i < row_original; i++)
  {
    for (int j = 0; j < column_original; j++)
    {
      sol[j * row_original + i] = m1[i * column_original + j];
    }
  }
  return;
}

//Matrix scalar maltiplication
void mat_mul_const(float *m1, float c, float *sol, int row, int column)
{
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < column; j++)
    {
      sol[i * column + j] = c * m1[i * column + j];
    }
  }
  return;
}

//Matrix inversion (by Gaussian elimination)
void mat_inv(float *m, float *sol, int column, int row)
{
  //allocate memory for a temporary matrix
  float* temp = (float *)malloc( column * 2 * row * sizeof(float) );

  //make the augmented matrix
  for (int i = 0; i < column; i++)
  {
    //copy original matrix
    for (int j = 0; j < row; j++)
    {
      temp[i * (2 * row) + j] = m[i * row + j];
    }

    //make identity matrix
    for (int j = row; j < row * 2; j++)
    {
      if (j - row == i)
      {
        temp[i * (2 * row) + j] = 1;
      }
      else
      {
        temp[i * (2 * row) + j] = 0;
      }
    }
  }

  //Sweep (down)
  for (int i = 0; i < column; i++)
  {
    //pivot selection
    float pivot = temp[i * (2 * row) + i];
    int pivot_index = i;
    float pivot_temp;
    for (int j = i; j < column; j++)
    {
      if ( temp[j * (2 * row) + i] > pivot )
      {
        pivot = temp[j * (2 * row) + i];
        pivot_index = j;
      }
    }
    if (pivot_index != i)
    {
      for (int j = 0; j < 2 * row; j++)
      {
        pivot_temp = temp[ pivot_index * (2 * row) + j ];
        temp[pivot_index * (2 * row) + j] = temp[i * (2 * row) + j];
        temp[i * (2 * row) + j] = pivot_temp;
      }
    }

    //division
    for (int j = 0; j < 2 * row; j++)
    {
      temp[i * (2 * row) + j] /= pivot;
    }

    //sweep
    for (int j = i + 1; j < column; j++)
    {
      float temp2 = temp[j * (2 * row) + i];

      //sweep each row
      for (int k = 0; k < row * 2; k++)
      {
        temp[j * (2 * row) + k] -= temp2 * temp[ i * (2 * row) + k ];
      }
    }
  }

  //Sweep (up)
  for (int i = 0; i < column - 1; i++)
  {
    for (int j = i + 1; j < column; j++)
    {
      float pivot = temp[ (column - 1 - j) * (2 * row) + (row - 1 - i)];
      for (int k = 0; k < 2 * row; k++)
      {
        temp[(column - 1 - j) * (2 * row) + k] -= pivot * temp[(column - 1 - i) * (2 * row) + k];
      }
    }
  }

  //copy result
  for (int i = 0; i < column; i++)
  {
    for (int j = 0; j < row; j++)
    {
      sol[i * row + j] = temp[i * (2 * row) + (j + row)];
    }
  }
  free(temp);
  return;
}

//=========================================================
//Kalman filter for "theta" & "theta_dot_bias"
//It takes 650 usec.
//=========================================================
void update_theta()
{
  updateIMU();

  //measurement data
  float x = ax; //degree

  //input data
  float theta_dot_gyro = gy; //degree/sec

  //calculate Kalman gain: G = P'C^T(W+CP'C^T)^-1
  float P_CT[2][1] = {};
  float tran_C_theta[2][1] = {};
  mat_tran(C_theta[0], tran_C_theta[0], 1, 2);//C^T
  mat_mul(P_theta_predict[0], tran_C_theta[0], P_CT[0], 2, 2, 2, 1);//P'C^T
  float G_temp1[1][1] = {};
  mat_mul(C_theta[0], P_CT[0], G_temp1[0], 1, 2, 2, 1); //CP'C^T
  float G_temp2 = 1.0f / (G_temp1[0][0] + theta_variance);//(W+CP'C^T)^-1
  float G[2][1] = {};
  mat_mul_const(P_CT[0], G_temp2, G[0], 2, 1);//P'C^T(W+CP'C^T)^-1

  //theta_data estimation: theta = theta'+G(x-Ctheta')
  float C_theta_theta[1][1] = {};
  mat_mul(C_theta[0], theta_data_predict[0], C_theta_theta[0], 1, 2, 2, 1);//Ctheta'
  float delta_x = x - C_theta_theta[0][0];//x-Ctheta'
  float delta_theta[2][1] = {};
  mat_mul_const(G[0], delta_x, delta_theta[0], 2, 1);
  mat_add(theta_data_predict[0], delta_theta[0], theta_data[0], 2, 1);

  //calculate covariance matrix: P=(I-GC)P'
  float GC[2][2] = {};
  float I2[2][2] = {{1, 0}, {0, 1}};
  mat_mul(G[0], C_theta[0], GC[0], 2, 1, 1, 2);//GC
  float I2_GC[2][2] = {};
  mat_sub(I2[0], GC[0], I2_GC[0], 2, 2);//I-GC
  mat_mul(I2_GC[0], P_theta_predict[0], P_theta[0], 2, 2, 2, 2);//(I-GC)P'

  //predict the next step data: theta'=Atheta+Bu
  float A_theta_theta[2][1] = {};
  float B_theta_dot[2][1] = {};
  mat_mul(A_theta[0], theta_data[0], A_theta_theta[0], 2, 2, 2, 1);//Atheta
  mat_mul_const(B_theta[0], theta_dot_gyro, B_theta_dot[0], 2, 1);//Bu
  mat_add(A_theta_theta[0], B_theta_dot[0], theta_data_predict[0], 2, 1);//Atheta+Bu

  //predict covariance matrix: P'=APA^T + BUB^T
  float AP[2][2] = {};
  float APAT[2][2] = {};
  float tran_A_theta[2][2] = {};
  mat_tran(A_theta[0], tran_A_theta[0], 2, 2);//A^T
  mat_mul(A_theta[0], P_theta[0], AP[0], 2, 2, 2, 2);//AP
  mat_mul(AP[0], tran_A_theta[0], APAT[0], 2, 2, 2, 2);//APA^T
  float BBT[2][2];
  float tran_B_theta[1][2] = {};
  mat_tran(B_theta[0], tran_B_theta[0], 2, 1);//B^T
  mat_mul(B_theta[0], tran_B_theta[0], BBT[0], 2, 1, 1, 2);//BB^T
  float BUBT[2][2] = {};
  mat_mul_const(BBT[0], theta_dot_variance, BUBT[0], 2, 2);//BUB^T
  mat_add(APAT[0], BUBT[0], P_theta_predict[0], 2, 2);//APA^T+BUB^T
}

void setupKF(void)
{
  //Kalman filter (angle) initialization
  //initial value of theta_data_predict
  theta_data_predict[0][0] = 0;
  theta_data_predict[1][0] = theta_dot_mean;

  //initial value of P_theta_predict
  P_theta_predict[0][0] = 1;
  P_theta_predict[0][1] = 0;
  P_theta_predict[1][0] = 0;
  P_theta_predict[1][1] = theta_dot_variance;
  
  Timer3.initialize(250000); //[usec]
  Timer3.attachInterrupt(update_theta);
}
