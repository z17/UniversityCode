function [] = funct1() 
%slCharacterEncoding('utf-8');
% кодирует шифром Цезаря

f1 = fopen('textin.txt','r');
str = fscanf(f1,'%c');
n = length(str);

offset = 1;
alf = 32;

for i = 1:1:n
    if double(str(i)) >= 224 & double(str(i)) <= 255
        str(i) = mod((double(str(i)) + offset),alf) + 224;
    end
end    

f2 = fopen('textout.txt','w');
fwrite(f2,str);

fclose(f1);
fclose(f2);

% Декодировщик 
f3 = fopen('textout.txt','r');
str = fscanf(f3,'%c');
n = length(str);

mas = [];
for i = 1:1:alf
    mas(i) = 0;
end

for i = 1:1:n
    if double(str(i)) >= 224 & double(str(i)) <= 255
        x = double(str(i)) - 223;
        x
        mas(char(x)) = mas(char(x)) + 1;        
    end
end 

mas = sort(mas);
mas


f4 = fopen('textout2.txt','w');
fwrite(f4,str);

fclose(f3);
fclose(f4);
end