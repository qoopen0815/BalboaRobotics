#pragma once
#include "matrix.h"


class Observer
{
public:
    std::vector<std::vector<float>> estimatedState( std::vector<std::vector<float>> oldStateX,
                                                    std::vector<std::vector<float>> inputU, 
                                                    std::vector<std::vector<float>> outputY);

private:
    const std::vector<std::vector<float>> sys_Ad = {
        {1.00261874869926, 0.0100091341522741, 0.0, 0.00337554714878429},
        {0.482653720733645,	1.00261874869926, 0.0, 0.522876594429155},
        {-0.00147616792255167, -5.57588987499912e-06, 1.0, 0.00455370509219353},
        {-0.228660309611543, -0.00147616792255167, 0.0, 0.156770137779705}
        };
    const std::vector<std::vector<float>> sys_Bd = {
        {-0.00999499408790945},
        {-1.54823743816105},
        {0.0161264775768699},
        {2.49680336732252}
        };
    const std::vector<std::vector<float>> C = {
        {0.0, 1.0, 1.0, 0.0}
        };
    const std::vector<std::vector<float>> L = {
        {0.403063593098180},
        {0.666909688967063},
        {-0.00490205378883404},
        {-0.0389174271114627}
        };
    const std::vector<std::vector<float>> K = {
        {-6.79854685968737, -1.15197482996310, -0.0902797948869708, -0.687737467443920}
        };
};
