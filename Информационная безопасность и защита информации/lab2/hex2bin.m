function bin=hex2bin(hex,n) 
    bin(1:n*4)='0'; 
    for i=1:n 
        d=hex2dec(hex(i)); 
        bin((i-1)*4+1:i*4)=dec2bin(d,4); 
    end 
end
