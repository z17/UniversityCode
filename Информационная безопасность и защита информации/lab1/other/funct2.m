function [] = funct2() 
f1 = fopen('textin.txt','r', 'n', 'windows-1251');
str = fscanf(f1,'%c');
n = length(str);

mas = ['а','б','в','г','д','е','ж','з','и','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ъ','ы','ь','э','ю','я'];
for i = 1:1:n
	double(str(i))
	mas(i);
end

fclose(f1);
end