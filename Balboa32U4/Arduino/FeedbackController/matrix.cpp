#include "matrix.h"

using matrix_function::MatrixFunction;

// Matrix addition
std::vector<std::vector<float>> MatrixFunction::mat_add(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2)
{
    std::vector<std::vector<float>> result(mat1.size(), std::vector<float>(mat1[0].size(), 0));

    if (mat1.size() == mat2.size())
    {
        if (mat1[0].size() == mat2[0].size())
        {
            float row = result.size();
            float col = result[0].size();

            for (float i = 0; i < row; i++)
            {
                for (float j = 0; j < col; j++)
                {
                    result[i][j] = mat1[i][j] + mat2[i][j];    
                }    
            }
        }
    }

    return result;
}

// Matrix subtraction
std::vector<std::vector<float>> MatrixFunction::mat_sub(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2)
{
    std::vector<std::vector<float>> result(mat1.size(), std::vector<float>(mat1[0].size(), 0));

    if (mat1.size() == mat2.size())
    {
        if (mat1[0].size() == mat2[0].size())
        {
            float row = result.size();
            float col = result[0].size();

            for (float i = 0; i < row; i++)
            {
                for (float j = 0; j < col; j++)
                {
                    result[i][j] = mat1[i][j] - mat2[i][j];    
                }    
            }
        }
    }

    return result;
}

// Matrix multiplication
std::vector<std::vector<float>> MatrixFunction::mat_mul(std::vector<std::vector<float>> mat1, std::vector<std::vector<float>> mat2)
{
    std::vector<std::vector<float>> result(mat1.size(), std::vector<float>(mat2[0].size(), 0));

    if (mat1[0].size() == mat2.size())
    {
        float row = result.size();
        float col = result[0].size();

        for (float i = 0; i < row; i++)
        {
            for (float j = 0; j < col; j++)
            {
                result[i][j] = 0;
                for (float k = 0; k < mat1[0].size(); k++)
                {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
    }

    return result;
}

// Matrix scaler multiplication
std::vector<std::vector<float>> MatrixFunction::mat_mul_const(const float c, std::vector<std::vector<float>> mat)
{
    std::vector<std::vector<float>> result(mat.size(), std::vector<float>(mat[0].size(), 0));

    float row = result.size();
    float col = result[0].size();

    for (float i = 0; i < row; i++)
    {
        for (float j = 0; j < col; j++)
        {
            result[i][j] = c * mat[i][j];
        }
    }

    return result;
}

// Matrix transposition
std::vector<std::vector<float>> MatrixFunction::mat_trans(std::vector<std::vector<float>> mat)
{
    std::vector<std::vector<float>> result(mat[0].size(), std::vector<float>(mat.size(), 0));

    float row = result.size();
    float col = result[0].size();

    for (float i = 0; i < row; i++)
    {
        for (float j = 0; j < col; j++)
        {
            result[i][j] = mat[j][i];
        }
    }

    return result;
}
