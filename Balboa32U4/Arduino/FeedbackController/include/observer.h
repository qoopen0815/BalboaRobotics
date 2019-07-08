#pragma once
#include "include/matrix.h"

class Observer
{
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
