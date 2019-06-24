% LQRƒpƒ‰ƒ[ƒ^
clear

balboa_param;
linear_model;

x_ref = [0; 0; 0; 10];

Q = diag([1 1 10 10]);
R = 1e+2;

K  = -lqr(sys_A, sys_B, Q, R);
Kd = -dlqr(sysd.A, sysd.B, Q, R);

x0 = [20*pi/180;0;0;0];