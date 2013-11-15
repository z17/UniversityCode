function [] = funct2() 

f1 = fopen('textin.txt','r', 'n', 'windows-1251');
str = fscanf(f1,'%c');
f2 = fopen('textout3.txt','w', 'n', 'windows-1251');
str
fprintf(f2,'%c',str);
fclose(f1);
fclose(f2);

end