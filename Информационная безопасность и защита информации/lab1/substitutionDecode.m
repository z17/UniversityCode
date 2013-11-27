function [] = substitutionDecode() 

% Декодировщик 2
% а б в г д е ж з и  й  к  л  м  н  о  п  р  с  т  у  ф  х  ц  ч  ш  щ  ъ  ы  ь  э  ю  я
% 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

f3 = fopen('textoutDECODE1.txt','r', 'n', 'windows-1251');
str = fscanf(f3,'%c');
alfTest = str;
n = length(str);

fl = false;

str1 = str;
str2 = str;
for i = 1:1:n
	if double(str(i)) >= 1072 & double(str(i)) <= 1103
		fl = true;
		if double(str(i)) - 1071 == 5 & fl == true
			str1(i) = 1071 + 2;
			fl = false;
		end
		if double(str(i)) - 1071 == 11 & fl == true
			str1(i) = 1071 + 20;
			fl = false;
		end
		if double(str(i)) - 1071 == 16 & fl == true
			str1(i) = 1071 + 7;
			fl = false;
		end
		if double(str(i)) - 1071 == 20 & fl == true
			str1(i) = 1071 + 22;
			fl = false;
		end
		if double(str(i)) - 1071 == 7 & fl == true
			str1(i) = 1071 + 19;
			fl = false;
		end
		if double(str(i)) - 1071 == 17 & fl == true
			str1(i) = 1071 + 28;
			fl = false;
		end
		if double(str(i)) - 1071 == 23 & fl == true
			str1(i) = 1071 + 9;
			fl = false;
		end
		if double(str(i)) - 1071 == 31 & fl == true
			str1(i) = 1071 + 13;
			fl = false;
		end
		if double(str(i)) - 1071 == 6 & fl == true
			str1(i) = 1071 + 3;
			fl = false;
		end
		if double(str(i)) - 1071 == 4 & fl == true
			str1(i) = 1071 + 18;
			fl = false;
		end
		if double(str(i)) - 1071 == 8 & fl == true
			str1(i) = 1071 + 17;
			fl = false;
		end
		if double(str(i)) - 1071 == 19 & fl == true
			str1(i) = 1071 + 8;
			fl = false;
		end
		if double(str(i)) - 1071 == 12 & fl == true
			str1(i) = 1071 + 5;
			fl = false;
		end
		if double(str(i)) - 1071 == 32 & fl == true
			str1(i) = 1071 + 11;
			fl = false;
		end
		if double(str(i)) - 1071 == 29 & fl == true
			str1(i) = 1071 + 12;
			fl = false;
		end
		if double(str(i)) - 1071 == 9 & fl == true
			str1(i) = 1071 + 4;
			fl = false;
		end
		if double(str(i)) - 1071 == 14 & fl == true
			str1(i) = 1071 + 6;
			fl = false;
		end			
		if double(str(i)) - 1071 == 3 & fl == true
			str1(i) = 1071 + 1;
			fl = false;
		end			
		if double(str(i)) - 1071 == 30 & fl == true
			str1(i) = 1071 + 14;
			fl = false;
		end			
   end
end

f4 = fopen('textoutDECODE2.txt','w', 'n', 'windows-1251');

fprintf(f4,'%c',str1);

fclose(f3);
fclose(f4);
end
