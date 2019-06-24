% 可制御性
clear

balboa_param;
linear_model;

% 可制御性のチェック（det_Vc≠0）
sys_Vc = ctrb(sys_Ad, sys_Bd)
rank_Vc = rank(sys_Vc)
det_Vc = det(sys_Vc)

% 可観測性のチェック
sys_Vo = obsv(sys_Ad, sys_C)
rank_Vo = rank(sys_Vo)
det_Vo = det(sys_Vo)
