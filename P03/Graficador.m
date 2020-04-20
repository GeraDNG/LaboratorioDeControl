clc
clear all
y = xlsread('NIDAM5V.csv');
ylabel('Vin (V)')
title('NIDAM 5V')
xlabel('T (ms)')
hold on;
plot(y)
legend('u(t)','y(t)')