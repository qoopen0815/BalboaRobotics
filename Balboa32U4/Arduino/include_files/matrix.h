#pragma once
#include <vector>

class MatrixFunction
{    
public:
    // Matrix addition
    std::vector<std::vector<float>> mat_add(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix subtraction
    std::vector<std::vector<float>> mat_sub(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix multiplication
    std::vector<std::vector<float>> mat_mul(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2);

    // Matrix scaler multiplication
    std::vector<std::vector<float>> mat_mul_const(const float c, std::vector<std::vector<float>> mat);

    // Matrix transposition
    std::vector<std::vector<float>> mat_trans(std::vector<std::vector<float>> mat);
    
    // Matrix inversion (by Gaussian elimination)
    // std::vector<std::vector<float>> mat_inv(std::vector<std::vector<float>> mat);
};
