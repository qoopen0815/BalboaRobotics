clear

balboa_param;

% 変数
a11 = (m_w + m_p)*power(r_w, 2) + 2*m_p*r_w*r_p + m_p*power(r_p, 2) + I_p + I_w;
a12 = (m_w + m_p)*power(r_w, 2) + m_p*r_w*r_p + I_w;
a21 = (m_w + m_p)*power(r_w, 2) + m_p*r_w*r_p + I_w;
a22 = (m_w + m_p)*power(r_w, 2) + I_w + power(n, 2)*I_m;

delta = a11*a22 - a12*a21;

% 状態方程式
sys_A = [0 1 0 0;
         (a22*m_p*g*r_p)/delta 0 0 (a12*power(n, 2)*k_t*k_b/R)/delta;
         0 0 0 1;
         (-a21*m_p*g*r_p)/delta 0 0 (-a11*power(n, 2)*k_t*k_b/R)/delta];

sys_B = [0;
         (-a12*n*k_t/R)/delta;
         0;
         (a11*n*k_t/R)/delta];

sys_C = eye(4);
sys_D = 0;

% 状態空間表現
sys = ss(sys_A, sys_B, sys_C, sys_D)
% 状態空間表現の係数の抽出
[sys_A, sys_B, sys_C, sys_D] = ssdata(sys)
% 状態空間表現から伝達関数表現（零点/極/ゲイン型）へ
zpk_P = zpk(sys)
% 離散化
Ts = 0.01; % 周期[sec]
sysd = c2d(sys, Ts, 'zoh');