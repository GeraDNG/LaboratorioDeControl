close all
clear all
clc

x = xlsread('Kp2_5ki0_3.csv',1,'A1:A5000');
y = xlsread('Kp2_5ki0_3.csv',1,'B1:B5000');
subplot(2,1,1);
plot(x,'r','linewidth',2);
title('Controlador PI, con una Kp=2.5 y Ki=0.3. Señal U(t)');
ylabel('Voltaje (V)');
xlabel('Tiempo (ms)');
grid on;
hold on;
subplot(2,1,2);
plot(y,'b','linewidth',2);
title('Controlador PI, con una Kp=2.5 y Ki=0.3. Señal Y(t)');
ylabel('Voltaje (V)');
xlabel('Tiempo (ms)');
grid on;
hold on;