%Выбор p и q с помощью теста Миллера-Рабина
prime = 0;
initValue = 20;

p = 0; q = 0;

format = 2^10;

while p*q < format
    if millerRabin(initValue, round(log2(initValue)))
        prime = prime + 1;
        if prime == 1
            p = initValue;
        end
        
        if prime == 6
            q = initValue;
            prime = 0;
        end    
    end
    
    initValue = initValue + 1;
end

n = p*q;
fn = (p-1)*(q-1);

%Нахождение e и d с помощью расширенного алгоритма Евклида 
initValue = 2;
while 1 
    [values] = extendedEvklid(fn, initValue);
    if(values{1} == 1)
        break;
    end
    initValue = initValue + 1;
end
e = initValue;
d = mod(values{3},fn);

%RSA шифрование
fileOutput = fopen('text1.txt', 'r');
message = fread(fileOutput, 'char');
fclose(fileOutput);

messageClone1 = message;
%fprintf(messageClone1);

for i = 1:length(message)
    message(i) = char(POW(message(i), e, n));
end

fileInput = fopen('textShifr.txt', 'w');
fwrite(fileInput, message, 'ubit11');
fclose(fileInput);


%RSA дешифрование
fileOutput = fopen('textShifr.txt', 'r');
message1 = fread(fileOutput, 'ubit11');
fclose(fileOutput);

message1Clone1 = message1;

for i = 1:length(message1)
    message1(i) = char(POW(message1(i), d, n));
end


fileInput = fopen('textDeShifr.txt', 'w');
fwrite(fileInput, message1, 'char');
fclose(fileInput);


