clear; format compact   %initialize

syms m_w r_w theta_w dtheta_w ddtheta_w I_w real % wheel
syms m_p r_p theta_p dtheta_p ddtheta_p I_p real % pendulum
syms n I_m k_t k_b R A real % motor/gear
syms theta_w dtheta_w ddtheta_w phi_p dphi_p ddphi_p real % radian
syms f_w g real % torque, gravity

q   = [theta_w theta_p]';
dq  = [dtheta_w dtheta_p]';
ddq = [ddtheta_w ddtheta_p]';
f   = [f_w 0]';

%--------------------------------------------------------

x_w = r_w*(q(1) + q(2));
y_w = 0;

dx_w = diff(x_w, q(1))*dq(1) + diff(x_w, q(2))*dq(2);
dy_w = diff(x_w, q(1))*dq(1) + diff(y_w, q(2))*dq(2);

x_p = x_w + r_p*sin(q(2));
y_p = r_p*cos(q(2));

dx_p = diff(x_p, q(1))*dq(1) + diff(x_p, q(2))*dq(2);
dy_p = diff(x_p, q(1))*dq(1) + diff(y_p, q(2))*dq(2);

f(1) = -n^2*I_m*ddq(1) - n^2*k_t*k_b*dq(1)/R + A;

%--------------------------------------------------------

K_w1 = 0.5*m_w*dx_w^2 + 0.5*m_w*dy_w^2;
K_w2 = 0.5*I_w*(dq(1) + dq(2))^2;
U_w = m_w*g*y_w;

K_p1 = 0.5*m_p*dx_p^2 + 0.5*m_p*dy_p^2;
K_p2 = 0.5*I_p*dq(2)^2;
U_p = m_p*g*y_p;

L = (K_w1 + K_w2 + K_p1 + K_p2) - (U_w + U_p);

%--------------------------------------------------------

N = length(q);
for i = 1:N
    dLq(i) = diff(L, dq(i));
    
    temp = 0;
    for j = 1:N
        temp = temp + diff(dLq(i),dq(j))*ddq(j) + diff(dLq(i),q(j))*dq(j);
    end
    ddLq(i) = temp;
    
    eq(i) = ddLq(i) - diff(L,q(i)) - f(i);
end

eq = simplify(eq')