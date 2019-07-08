#pragma once
#include "matrix.h"

//---------------------------------
//     通常のコンストラクタ
//---------------------------------
Matrix::Matrix(int i, int j)
{
    row = i;
    col = j;

    //  配列のメモリ領域を動的に確保
    p_top = new double*[row+1];
    *p_top = new double[row*col+1]; 
    for(int k=1; k<=row; k++)
    {
        *(p_top+k) = *p_top+((k-1)*col);
    }

    //  値の初期化
    for(int k1=1; k1<=row; k1++)
    {
        for(int k2=1; k2<=col; k2++)
        {
            p_top[k1][k2] = 0;
        }
    }
}

//---------------------------------
//     コピーコンストラクタ
//---------------------------------
Matrix::Matrix(const Matrix &cp)
{
    row = cp.row;
    col = cp.col;

    // 配列のメモリ領域を動的に確保
    p_top = new double*[row+1];
    *p_top = new double[row*col+1]; 
    for(int k=1; k<=row; k++)
    { 
        *(p_top+k) = *p_top+((k-1)*col);
    }

    // 値のコピー
    for(int k1=1; k1<=row; k1++)
    {
        for(int k2=1; k2<=col; k2++)
        {
            p_top[k1][k2] = cp.p_top[k1][k2];
        }
    }
}

//----------------------
//   デストラクタ
//----------------------
Matrix::~Matrix()
{
    delete [] *p_top; 
    delete [] p_top;
}

//------------------------------
//   行列の大きさを変える  値は０
//------------------------------
void Matrix::change_size(int i, int j)
{
    //  i,j のチェック
    if( i<1 || j<1 )
    {
        // Serial.println(F("err Matrix::change_size"));
        // delay(100);
    }

    delete [] *p_top; 
    delete [] p_top;

    row = i;
    col = j;

    //  配列のメモリ領域を動的に確保
    p_top = new double*[row+1];
    *p_top = new double[row*col+1]; 
    for(int k=1; k<=row; k++)
    {
        *(p_top+k) = *p_top+((k-1)*col);
    }

    //  値の初期化
    for(int k1=1; k1<=row; k1++)
    {
        for(int k2=1; k2<=col; k2++)
        {
            p_top[k1][k2] = 0;
        }
    }
}

//------------------------------------
//     代入
//------------------------------------
Matrix Matrix::operator=(const Matrix &a)
{
    if( row != a.row || col != a.col )
    {
        change_size(a.row, a.col);
    }

    for(int i=1; i<=row; i++)
    {
        for(int j=1; j<=col; j++)
        {
            p_top[i][j] = a.p_top[i][j];
        }
    }
    return(*this);
}

//------------------------------------
//       行列の加算
//------------------------------------
Matrix Matrix::operator+(const Matrix &a)
{
    if( row != a.row || col != a.col )
    {
        // Serial.println(F("err Matrix::operator+ not equal matrix size"));
        // delay(100);
    }

    Matrix r(row, col);
    for(int i=1; i<=row; i++)
    {
        for(int j=1; j<=col; j++)
        {
            r.p_top[i][j] = p_top[i][j] + a.p_top[i][j];
        }
    }
    return(r);
}

//------------------------------------
//       行列の減算
//------------------------------------
Matrix Matrix::operator-(const Matrix &a)
{
    if( row != a.row || col != a.col )
    {
        // Serial.println(F("err Matrix::operator- not equal matrix size"));
        // delay(100);
    }

    Matrix r(row, col);
    for(int i=1; i<=row; i++)
    {
        for(int j=1; j<=col; j++)
        {
            r.p_top[i][j] = p_top[i][j] - a.p_top[i][j];
        }
    }
    return(r);
}

//------------------------------------
//       行列の積
//------------------------------------
Matrix Matrix::operator*(const Matrix &a)
{
    if( col != a.row )
    {
        // Serial.println(F("err Matrix::operator* not equal matrix size"));
        // delay(100);
    }

    Matrix r(row, a.col);
    for(int i=1; i<=row; i++)
    {
        for(int j=1; j<=a.col; j++)
        {
            for(int k=1; k<=col; k++)
            {
                r.p_top[i][j] += p_top[i][k] * a.p_top[k][j];
            }
        }
    }
    return(r);
}

//--------------------------------------
//       行列の定数倍
//--------------------------------------
Matrix operator*(const Matrix &a, double b)
{
    Matrix r(a.row, a.col);
    for(int i=1; i<=a.row; i++)
    {
        for(int j=1; j<=a.col; j++)
        {
            r[i][j] = b * a.p_top[i][j];
        }
    }
    return(r);
}
Matrix operator*(double b, const Matrix &a)
{
    Matrix r(a.row, a.col);
    for(int i=1; i<=a.row; i++)
    {
        for(int j=1; j<=a.col; j++)
        {
            r[i][j] = b * a.p_top[i][j];
        }
    }
    return(r);
}

//----------------------------------------
//  単位行列にする
//----------------------------------------
void Matrix::unit_matrix()
{
    if(row != col)
    {
        // Serial.println(F("err in Matrix::unit_matrix()"));
        // delay(100);
    }

    int n = row;
    double** a = p_top;
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            a[i][j] = 0;
            if(i == j) a[i][j] = 1;
        }
    }

}

//----------------------------------------
//  転置行列をかえす
//----------------------------------------
Matrix Matrix::transposed()
{
    Matrix t(col, row);
    double** a = p_top;

    for(int i=1; i<=row; i++)
    {
        for(int j=1; j<=col; j++)
        {
            t[j][i] = a[i][j];
        }
    }
    return(t);
}
