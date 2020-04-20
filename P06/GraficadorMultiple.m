clear all
close all
clc

t=linspace(1,5000,5000);

x1=xlsread('H1y-1.csv',1,'A1:A5000');
x2=xlsread('H2y-2.csv',1,'A1:A5000');
x3=xlsread('H3y-3.csv',1,'A1:A5000');
x4=xlsread('H10y-10.csv',1,'A1:A5000');
x5=xlsread('H15y-15.csv',1,'A1:A5000');

y1=xlsread('H1y-1.csv',1,'B1:B5000');
y2=xlsread('H2y-2.csv',1,'B1:B5000');
y3=xlsread('H3y-3.csv',1,'B1:B5000');
y4=xlsread('H10y-10.csv',1,'B1:B5000');
y5=xlsread('H15y-15.csv',1,'B1:B5000');

figure();

subplot(2,1,1);
plot(t,x1);
hold on;
plot(t,x2);
hold on;
plot(t,x3);
hold on;
plot(t,x4);
hold on;
plot(t,x5);
hold on;
title('Controlador ON/OFF con Histéresis, salida del proceso U(t)');
xlabel('Tiempo (ms)');
ylabel('Voltaje (V)');
grid on;
legend('Ventana=+-1','Ventana=+-2','Ventana=+-3','Ventana=+-10','Ventana=+-15');

subplot(2,1,2);
plot(t,y1);
hold on;
plot(t,y2);
hold on;
plot(t,y3);
hold on;
plot(t,y4);
hold on;
plot(t,y5);
hold on;
title('Controlador ON/OFF con Histéresis, salida del proceso Y(t)');
xlabel('Tiempo (ms)');
ylabel('Voltaje (V)');
grid on;
legend('Ventana=+-1','Ventana=+-2','Ventana=+-3','Ventana=+-10','Ventana=+-15');