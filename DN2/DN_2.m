clear; clc; close all;

fid = fopen('vozlisca_temperature_dn2_10.txt','r');
fgetl(fid);

vr = fgetl(fid); N_x = sscanf(vr,'st. koordinat v x-smeri: %f');
vr = fgetl(fid); N_y = sscanf(vr,'st. koordinat v y-smeri: %f');
vr = fgetl(fid); N_v = sscanf(vr,'st. vseh vozlisc: %f');

podatki = readmatrix('vozlisca_temperature_dn2_10.txt','NumHeaderLines',4);
x_v = podatki(:,1); 
y_v = podatki(:,2); 
T_v = podatki(:,3);
fclose(fid);


fid = fopen('celice_dn2_10.txt','r');
fgetl(fid);
vr = fgetl(fid); 
N_c = sscanf(vr,'st. celic: %f');
vse = readmatrix('celice_dn2_10.txt','NumHeaderLines',2);
fclose(fid);

x_u = unique(x_v);
y_u = unique(y_v);
Tmat = reshape(T_v,[N_x,N_y])';


xq = 0.403; 
yq = 0.503;

tic;
F_1 = scatteredInterpolant(x_v,y_v,T_v,'linear');
T_1 = F_1(xq,yq);
t_1 = toc;

fprintf("[1] scattered -> %.6f °C, čas = %.6f s\n", T_1, t_1);

tic;
F_2 = griddedInterpolant({y_u,x_u},Tmat,'linear');
T_2 = F_2(yq,xq);
t_2 = toc;

fprintf("[2] gridded -> %.6f °C, čas = %.6f s\n", T_2, t_2);

tic;
ix = find(x_u <= xq,1,'last');
iy = find(y_u <= yq,1,'last');

x_1 = x_u(ix);   x_2 = x_u(ix+1);
y_1 = y_u(iy);   y_2 = y_u(iy+1);

T_11 = Tmat(iy,ix);
T_21 = Tmat(iy,ix+1);
T_12 = Tmat(iy+1,ix);
T_22 = Tmat(iy+1,ix+1);

K_1 = (x_2-xq)/(x_2-x_1)*T_11 + (xq-x_1)/(x_2-x_1)*T_21;
K_2 = (x_2-xq)/(x_2-x_1)*T_12 + (xq-x_1)/(x_2-x_1)*T_22;

T_3 = (y_2-yq)/(y_2-y_1)*K_1 + (yq-y_1)/(y_2-y_1)*K_2;

t_3 = toc;

fprintf("[3] bilinear -> %.6f °C, čas = %.6f s\n", T_3, t_3);

[Tmax, idx] = max(T_v);
fprintf("Tmax = %.6f °C pri (%.6f , %.6f)\n", Tmax, x_v(idx), y_v(idx));