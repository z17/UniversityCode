function [] = functcaesar() 

% кодирует шифром Цезаря
f1 = fopen('textin.txt','r', 'n', 'windows-1251');
str = fscanf(f1,'%c');
n = length(str);

offset = 1;
alf = 32;
for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		str(i) = mod((double(str(i)) - 1072 + offset),alf) + 1072;	
   end
end
f2 = fopen('сaesarOutCode.txt','w', 'n', 'windows-1251');

fprintf(f2,'%c',str);
fclose(f1);
fclose(f2);


% Декодировщик перебором

f3 = fopen('F6_ciph_ces.txt','r', 'n', 'windows-1251');
str = fscanf(f3,'%c');
fclose(f3);	
n = length(str);
	
for j = 1:1:alf
	str1 = str;
	for i = 1:1:n
		if double(str(i)) >= 1072 & double(str(i)) <= 1103
			str1(i) = mod((double(str(i)) - 1072 - j),alf) + 1072;	
	   end
	end	
	name = strcat('caesar/caesarOutDecode',int2str(j),'.txt');
	f4 = fopen(name,'w', 'n', 'windows-1251');
	fprintf(f4,'%c',str1);
	fclose(f4);	
end
