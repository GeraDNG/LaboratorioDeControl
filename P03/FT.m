clear all;
close all;
clc

s=tf('s');

%Función de Transferencia:
tao=(0.121+0.124+0.171)/3.0;
k=(((2.98/3)+(1.843/2)+(4.98/ 5))/3)-0.007;
Gps=k/(tao*s+1);

%NIDAM 1V:
v1=0.7647;
M1=1;
tao1=0.121;
k1=v1/M1;
Gps1=k1/(tao1*s+1);
step(Gps1, 'r');
ylabel('Amplitude (V)');
title('FT');
grid on;
hold on;

%FT 1V:
step(Gps, 'r');
hold on;

%NIDAM 2V:
v2=1.843;
M2=2;
tao2=0.105;
k2=v2/M2;
Gps2=k2*2/(tao2*s+1);
step(Gps2, 'g');
hold on;

%FT 2V:
step(Gps*2, 'g');
hold on;

%NIDAM 3V:
v3=2.98;
M3=3;
tao3=0.124;
k3=v3/M3;
Gps3=k3*3/(tao3*s+1);
step(Gps3, 'b');
hold on;

%FT 3V:
step(Gps*3, 'b');
hold on;

%NIDAM 4V:
v4=4.11;
M4=4;
tao4=0.171;
k4=v4/M4;
Gps4=k4*4/(tao4*s+1);
step(Gps4, 'm');
hold on;

%FT 4V:
step(Gps*4, 'm');
hold on;

%NIDAM 5V:
v5=4.98;
M5=5;
tao5=0.215;
k5=v5/M5;
Gps5=k5*5/(tao5*s+1);
step(Gps5, 'y');
hold on;

%FT 5V:
step(Gps*5, 'y');
hold on;

legend('NIDAM 1V','FT 1V', 'NIDAM 2V','FT 2V', 'NIDAM 3V','FT 3V', 'NIDAM 4V','FT 4V', 'NIDAM 5V','FT 5V');