close all;

thr_input = 0:1:99;

pointsx = [1,10,15,30,40,50,60,70,80,85,90,100,110];
pointsy = [0,0.07,0.24,0.26,0.32,0.4,0.47,0.53,0.57,0.57,0.64,1.2,1.4];
thr_curve = polyval(polyfit(pointsx, pointsy, 5), thr_input);
thr_curve(thr_curve>1) = 1;
thr_curve(thr_curve<0) = 0;

pointsx = [1,10,15,30,40,50,60,70,80,85,90,100,110];
pointsy = [0,0.05,0.18,0.19,0.21,0.34,0.38,0.4,0.42,0.5,0.8,1,1.25];
thr_curve2 = polyval(polyfit(pointsx, pointsy, 5), thr_input);
thr_curve2(thr_curve2>1) = 1;
thr_curve2(thr_curve2<0) = 0;

pointsx = [1,10,15,30,40,50,60,70,80,85,90,100,110];
pointsy = [0,0.04,0.1,0.12,0.12,0.22,0.28,0.32,0.37,0.51,0.59,0.89,1.1];
thr_curve3 = polyval(polyfit(pointsx, pointsy, 5), thr_input);
thr_curve3(thr_curve3>1) = 1;
thr_curve3(thr_curve3<0) = 0;

pointsx = [1,10,15,30,40,50,60,70,80,85,90,100,110];
pointsy = [0,0.1,0.15,0.26,0.32,0.38,0.42,0.51,0.62,0.78,0.87,1,1.25] .* 0.24;
thr_curve4 = polyval(polyfit(pointsx, pointsy, 6), thr_input);
thr_curve4(thr_curve4>1) = 1;
thr_curve4(thr_curve4<0) = 0;

for i=thr_input+1
    thr_curve(i) = thr_curve(i);
	thr_curve2(i) = thr_curve2(i);
	thr_curve3(i) = thr_curve3(i);
	thr_curve4(i) = thr_curve4(i);
end

figure(1)
hold on;
plot(thr_curve, 'x'); 
plot(thr_curve2, 'x');
plot(thr_curve3, 'x');
plot(thr_curve4, 'x');
title('Thorttle curve')
xlabel('Throttle [%]')
ylabel('Current [% I_{max}]')
legend('Extreme', 'Sport', 'Eco', 'Kids')

clc;
fprintf("\n");
fprintf("static const float aw_curve_vinga_extreme[] = {%s};\n", regexprep(num2str(thr_curve),'\s+',','));
fprintf("static const float aw_curve_vinga_sport[] = {%s};\n", regexprep(num2str(thr_curve2),'\s+',','));
fprintf("static const float aw_curve_vinga_eco[] = {%s};\n", regexprep(num2str(thr_curve3),'\s+',','));
fprintf("static const float aw_curve_vinga_kids[] = {%s};\n", regexprep(num2str(thr_curve4),'\s+',','));
fprintf("\n");