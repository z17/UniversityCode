function bool = witness(a,p)

b = de2bi(p-1);
d = 1;

for i = length(b):-1:1
    x = d;
    d = mod(d*d,p);
    
    if d == 1 && x ~= 1 && x ~= p-1
        bool = true;
        return;
    end
    
    if b(i) == 1
        d = mod(d*a,p);
    end
end

if d ~= 1
    bool = true;
    return;
end

bool = false;
return;