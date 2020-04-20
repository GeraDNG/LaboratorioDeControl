clc
clear all
y = xlsread('P02_021.csv');
ylabel('Voltage')
title('Step 1V')
xlabel('t')
hold on;
plot(y)