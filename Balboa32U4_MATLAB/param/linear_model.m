clear
balboa_param;

% 変数
a11 = (m_w + m_p)*r_w*r_w + 2*m_p*r_w*r_p + m_p*r_p*r_p + I_p + I_w;
a12 = (m_w + m_p)*r_w*r_w + m_p*r_w*r_p + I_w;
a21 = (m_w + m_p)*r_w*r_w + m_p*r_w*r_p + I_w;
a22 = (m_w + m_p)*r_w*r_w + I_w + n*n*I_m;
delta = a11*a22 - a12*a21;

% 状態方程式（連続系）
sys_A = [0 1 0 0;
         (a22*m_p*g*r_p)/delta 0 0 (a12*n*n*k_t*k_b/R)/delta;
         0 0 0 1;
         (-a21*m_p*g*r_p)/delta 0 0 (-a11*n*n*k_t*k_b/R)/delta];
sys_B = [0;
         (-a12*n*k_t/R)/delta;
         0;
         (a11*n*k_t/R)/delta];
sys_C = [0 0 0 0;
         0 1 0 0;
         0 0 1 0;
         0 0 0 0];
sys_D = [0;
         0;
         0;
         0];

% 離散化
syms Ts real
Ts = 0.01; % [sec]
[sys_Ad, sys_Bd] = c2d(sys_A, sys_B, Ts);

% 状態空間表現（連続系）
sys = ss(sys_A, sys_B, sys_C, sys_D);
% 状態空間表現（離散系）
sysd = ss(sys_Ad, sys_Bd, sys_C, sys_D, Ts);
% 状態空間表現から伝達関数表現（零点/極/ゲイン型）へ
zpk = zpk(sys);