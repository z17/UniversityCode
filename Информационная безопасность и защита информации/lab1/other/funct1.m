function [] = funct1() 
%slCharacterEncoding('utf-8');
% кодирует шифром Цезаря

f1 = fopen('textin.txt','r', 'n', 'windows-1251');
str = fscanf(f1,'%c');
n = length(str);

offset = 29;
alf = 32;
s = '------------'
for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		str(i) = mod((double(str(i)) - 1072 + offset),alf) + 1072;	
   end
end
f2 = fopen('textoutCODE.txt','w', 'n', 'windows-1251');

fprintf(f2,'%c',str);
fclose(f1);
fclose(f2);

% Декодировщик 
% Самые частые буквы - О и Е: 1086 и 1077 или 15 и 6-е буквы в алфавите
f3 = fopen('F6_ciph_ces.txt','r', 'n', 'windows-1251');
str = fscanf(f3,'%c');
n = length(str);

mas = [];
for i = 1:1:alf
    mas(i) = 0;
end
for i = 1:1:n
    if double(str(i)) >=  1072 & double(str(i)) <=  11035
        x = double(str(i)) - 1071;
        mas(x) = mas(x) + 1;        
    end
end 

max1 = mas(1);
max2 = mas(1);
max1Ind = 0;
max2Ind = 0;
mas
for i = 1:1:alf
    if mas(i) > max1;
		max2 = max1;
		max2Ind = max1Ind;
		max1 = mas(i);
		max1Ind = i;
	end
	if mas(i) > max2 & mas(i) < max1
		max2 = mas(i);
		max2Ind = i;
	end
end

max1
max2
max1Ind =  max1Ind+1;
max2Ind =  max2Ind+1;
delta1 = max1Ind - 15 - 1
delta2 = max2Ind - 6 - 1
str1 = str;
str2 = str;
for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		str1(i) = mod((double(str(i)) - 1072 - delta1),alf) + 1072;	
		str2(i) = mod((double(str(i)) - 1072 - delta2),alf) + 1072;	
   end
end

f4 = fopen('textoutDECODE1.txt','w', 'n', 'windows-1251');
f5 = fopen('textoutDECODE2.txt','w', 'n', 'windows-1251');

fprintf(f4,'%c',str1);
fprintf(f5,'%c',str2);

fclose(f3);
fclose(f4);
fclose(f5);
end