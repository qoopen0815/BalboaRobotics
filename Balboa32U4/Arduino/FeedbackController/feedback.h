#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <vector>
#include "matrix.h"

namespace feedback_function
{
class FeedbackFunction
{
public:
    FeedbackFunction(std::vector<std::vector<float>> A, std::vector<std::vector<float>> B, std::vector<std::vector<float>> C, std::vector<std::vector<float>> K, std::vector<std::vector<float>> L);

    std::vector<std::vector<float>> getCommandValue(std::vector<std::vector<float>> gainK, std::vector<std::vector<float>> stateX);

    std::vector<std::vector<float>> observer(std::vector<std::vector<float>> oldStateX, float inputU, float outputY);

    std::vector<std::vector<float>> A_;
    std::vector<std::vector<float>> B_;
    std::vector<std::vector<float>> C_;
    std::vector<std::vector<float>> K_;
    std::vector<std::vector<float>> L_;
};
}

#endif
