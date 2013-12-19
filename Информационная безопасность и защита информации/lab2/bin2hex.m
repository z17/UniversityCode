function hex=bin2hex(bin,n) 
    hex(1:n)='0'; 
    for i=1:n 
        d=bin2dec(bin((i-1)*4+1:i*4)); 
        hex(i)=dec2hex(d); 
    end 
end