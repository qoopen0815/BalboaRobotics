# Balboa32U4-MATLAB
MATLAB code for [Balboa32U4](https://www.pololu.com/docs/0J70)

## Inverted pendulum
- [parameter](https://github.com/calm0815/BalboaRobotics/tree/master/Balboa32U4_MATLAB/param)

    - [balboa_param.m](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/param/balboa_param.m)  
    Basic Configuration

    - [lagrange.m](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/param/lagrange.m)  
    Derivation of Lagrange's equation of motion

    - [linear_model.m](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/param/linear_model.m)  
    Linear approximation model of Balboa32U4

- [Feedback Controller](https://github.com/calm0815/BalboaRobotics/tree/master/Balboa32U4_MATLAB/FeedbackController)

    - [Checker](https://github.com/calm0815/BalboaRobotics/tree/master/Balboa32U4_MATLAB/FeedbackController/checker)  
    check "Controllability", "Observability"

    - Simulation
        - [FeedbackControl (continuous)](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/FeedbackController/FeedbackControl_continuous.slx)  

        - [FeedbackControl (descrete)](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/FeedbackController/FeedbackControl_descrete.slx)  

        - [FeedbackControl using observer (descrete)](https://github.com/calm0815/BalboaRobotics/blob/master/Balboa32U4_MATLAB/FeedbackController/FeedbackControl_observer_descrete.slx)  