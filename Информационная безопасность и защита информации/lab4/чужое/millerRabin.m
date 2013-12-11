function bool = millerRabin(p,s)

for i = 1:s
    a = randi([1, p-1]);
    if witness(a, p)
        bool = false;
        return;
    end
    
    bool = true;
    return;
end