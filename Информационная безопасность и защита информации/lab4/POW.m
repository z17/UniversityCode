function f = POW(a, n, m)
set(0,'RecursionLimit',1000);
if n == 1
    f = mod(a, m);
else
    if mod(n, 2) == 0
        z = POW(a, n/2, m);
        f = mod(z^2, m);
    else
        z = POW(a, (n-1)/2, m);
        f = mod(a*z^2, m);
    end
end