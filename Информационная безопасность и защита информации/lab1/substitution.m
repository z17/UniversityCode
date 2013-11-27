function [] = substitution() 

start = '---------------------------------'
alf = 32;
% кодирует подстановочным шифром
f1 = fopen('textin.txt','r', 'n', 'windows-1251');
str = fscanf(f1,'%c');
n = length(str);

arraySub = [3, 5, 6, 9, 12, 14, 16, 19, 23, 25, 32, 29 , 31, 30, 1, 2, 8, 4, 7, 11, 24, 20, 15, 10, 13, 28, 22, 17, 18, 21, 26, 27];

for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		str(i) = arraySub(double(str(i)) - 1071) + 1071;	
   end
end

f2 = fopen('substitutionOutCode.txt','w', 'n', 'windows-1251');
fprintf(f2,'%c',str);


fclose(f1);
fclose(f2);


% Декодировщик 
% Самые частые буквы - О и Е: 1086 и 1077 или 15 и 6-е буквы в алфавите
f3 = fopen('substitutionOutCode.txt','r', 'n', 'windows-1251');
str = fscanf(f3,'%c');
alfTest = str;
n = length(str);

mas = [];
% заполняем массив нулями
for i = 1:1:alf
    mas(i) = 0;
end
for i = 1:1:n
    if double(str(i)) >=  1072 & double(str(i)) <=  1103
        x = double(str(i)) - 1071;
        mas(x) = mas(x) + 1;        
    end
end 
mas

max1 = 0;
max2 = 0;
max1Ind = 0;
max2Ind = 0;
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

max1Ind = max1Ind - 1;
max2Ind = max2Ind - 1;

str1 = str;
str2 = str;
for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		if double(str(i)) - 1072 == max1Ind
			str1(i) = 1071 + 15;
		end			
   end
end

f4 = fopen('textoutDECODE1.txt','w', 'n', 'windows-1251');

fprintf(f4,'%c',str1);

fclose(f3);
fclose(f4);
end
