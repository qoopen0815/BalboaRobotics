#include "feedback.h"

using matrix_function::MatrixFunction;
using feedback_function::FeedbackFunction;

FeedbackFunction::FeedbackFunction(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> C, std::vector<std::vector<float>> K, std::vector<std::vector<float>> L)
{
    A_ = A;
    B_ = B;
    C_ = C;
    K_ = K;
    L_ = L;
}

std::vector<std::vector<float>> FeedbackFunction::getCommandValue(std::vector<std::vector<float>> gainK, std::vector<std::vector<float>> stateX)
{
    std::vector<std::vector<float>> commandValue = MatrixFunction::mat_mul(gainK, stateX);

    return commandValue;
}

std::vector<std::vector<float>> FeedbackFunction::observer(std::vector<std::vector<float>> stateX, float inputU, float outputY)
{
    std::vector<std::vector<float>> LC = MatrixFunction::mat_mul(L_, C_);
    std::vector<std::vector<float>> A_LC = MatrixFunction::mat_sub(A_, LC);
    std::vector<std::vector<float>> A_LCX = MatrixFunction::mat_mul(A_LC, stateX);
    std::vector<std::vector<float>> Bu = MatrixFunction::mat_mul_const(inputU, B_);
    std::vector<std::vector<float>> Ly = MatrixFunction::mat_mul_const(outputY, L_);
    std::vector<std::vector<float>> Bu_Ly = MatrixFunction::mat_add(Bu, Ly);
    std::vector<std::vector<float>> estimatedX = MatrixFunction::mat_add(A_LCX, Bu_Ly);

    return estimatedX;
}