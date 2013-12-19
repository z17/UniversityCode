function c=mxor(a,b,n) 
    c(1:n)='0'; 
    for j = 1:n 
        if a(j)==b(j) 
            c(j)='0'; 
        else 
            c(j)='1'; 
        end 
    end 
end
