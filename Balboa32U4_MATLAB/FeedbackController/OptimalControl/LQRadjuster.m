% LQRƒpƒ‰ƒ[ƒ^
clear

balboa_param;
linear_model;

x_ref = [0; 0; 0; 10];

Q = diag([10 1 1 1]);
R = 1e+5;

K  = -lqr(sys_A, sys_B, Q, R)
Kd = -dlqr(sys_Ad, sys_Bd, Q, R)

x0 = [20*pi/180;0;0;0];