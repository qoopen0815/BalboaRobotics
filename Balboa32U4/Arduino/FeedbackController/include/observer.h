#pragma once
#include "matrix.h"

class Observer
{
    double A[4][4] = {
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1}
    };

public:
    Observer(void); // constructor
    void updateState(void); 

private:
    Matrix observedState(Matrix oldStateX, Matrix inputU, Matrix outputY);

private:
    Matrix A_;
    Matrix B_;
    Matrix C_;
    Matrix L_;
};
