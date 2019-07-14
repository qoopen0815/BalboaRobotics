#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

namespace matrix_function 
{
class MatrixFunction
{    
public:
    // Matrix addition
    static std::vector<std::vector<float>> mat_add(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix subtraction
    static std::vector<std::vector<float>> mat_sub(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix multiplication
    static std::vector<std::vector<float>> mat_mul(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix scaler multiplication
    static std::vector<std::vector<float>> mat_mul_const(const float c, std::vector<std::vector<float>> mat);

    // Matrix transposition
    static std::vector<std::vector<float>> mat_trans(std::vector<std::vector<float>> mat);
    
    // Matrix inversion (by Gaussian elimination)
    // static std::vector<std::vector<float>> mat_inv(std::vector<std::vector<float>> mat);
};
}

#endif