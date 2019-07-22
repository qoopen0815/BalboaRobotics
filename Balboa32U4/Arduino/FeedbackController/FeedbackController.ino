#include <Wire.h>
#include <Balboa32U4.h>
#include <BasicLinearAlgebra.h>
#include <StateSpaceControl.h>
#include "conversion.hpp"
#include "nine_axis_IMU.hpp"

using namespace BLA;

struct Balboa32U4Model : public Model<4,1,1>
{
    Balboa32U4Model(void)
    {
        A<< 1.00261874869926,       0.0100091341522741,     0.0,    0.00337554714878429,
            0.482653720733645,	    1.00261874869926,       0.0,    0.522876594429155,
            -0.00147616792255167,   -5.57588987499912e-06,  1.0,    0.00455370509219353,
            -0.228660309611543,     -0.00147616792255167,   0.0,    0.156770137779705;

        B<< -0.00999499408790945,
            -1.54823743816105,
            0.0161264775768699,
            2.49680336732252;

        C<< 0, 1, 1, 0;

        D = Zeros<1,1>();
    }
};

const float Ts = 10.0;  //周期Ts [ms]
const float Voffset = 0.3768;  //オフセット電圧 [V]
const float Vmax = 5.85;  //最大入力電圧 [V]

Balboa32U4Encoders encoders;
Balboa32U4Motors motors;
Balboa32U4Model model;
StateSpaceController<4,1,4,true,false,false> controller(model);
Matrix<4> y;

static unsigned long startTime = 0;
static unsigned long goalTime = 0;
static unsigned long processTime = 0;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    setupIMU();

    controller.K << 7.63792168712424,	1.29476574428372,	0.230902782597325,  0.757147631076487;
    controller.L << 0.0,    2.43655257554095,       -7.16849763516007,	0.0,
                    0.0,	1.92221702492044,	    -2.31910609760691,	0.0,
                    0.0,	-0.0213622848683981,	1.23979061025779,	0.0,
                    0.0,	-0.666199988097829,	    1.63444679177167,	0.0;

    // Once the system and gain matrices are filled in, the controller needs to be initialised so that it can precalculate Nbar
    controller.initialise();

    // Try to bring the cart to rest at 3.5m from it's home position
    controller.r << 0, 0, 0, 0;
}

void loop()
{
    startTime = millis();

    updateIMU();

    y << 0, deg2rad(gy), en2rad(encoders.getCountsLeft()), 0;

    controller.update(y, Ts*0.001);
    int input = -1 * controller.u(0,0) * 300/Vmax;

    motors.setSpeeds(input, input);

    Serial << "x_hat = " << controller.x_hat << '\t' << "u=" << controller.u << '\n';

    goalTime = millis();
    delay(Ts - (goalTime - startTime));
}
