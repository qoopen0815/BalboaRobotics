clear
balboa_param;
linear_model;

q = [1/3 -1/4 1/4 -1/3];
L = place(sys_Ad',sys_C',q).';

% LQR optimization
Q = diag([10 1 10 10]);
R = 1e+2;
K  = -lqr(sys_A, sys_B, Q, R);
Kd = -dlqr(sys_Ad, sys_Bd, Q, R);

x0 = [20*pi/180;0;0;0];