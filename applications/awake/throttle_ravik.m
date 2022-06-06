close all;

thr_input = 0:1:99;

pointsx = [1,10,15,30,40,50,60,70,80,85,90,100];
pointsy = [0,0.2,0.23,0.36,0.52,0.55,0.63,0.68,0.79,0.87,0.95,1];
p = polyval(polyfit(pointsx, pointsy, 5), thr_input);
p(p>1) = 1;
p(p<0) = 0;

thr_curve = p;
thr_curve2 = p;
thr_curve3 = p;
thr_curve4 = p;

for i=thr_input+1
    thr_curve(i) = thr_curve(i)     *   1.00; % extreme
	thr_curve2(i) = thr_curve2(i)   *   0.78; % sport
	thr_curve3(i) = thr_curve3(i)   *   0.64; % eco
	thr_curve4(i) = thr_curve4(i)   *   0.38; % slow
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
fprintf("static const float aw_curve_ravik_extreme[] = {%s};\n", regexprep(num2str(thr_curve),'\s+',','));
fprintf("static const float aw_curve_ravik_sport[] = {%s};\n", regexprep(num2str(thr_curve2),'\s+',','));
fprintf("static const float aw_curve_ravik_eco[] = {%s};\n", regexprep(num2str(thr_curve3),'\s+',','));
fprintf("static const float aw_curve_ravik_kids[] = {%s};\n", regexprep(num2str(thr_curve4),'\s+',','));
fprintf("\n");