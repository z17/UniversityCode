function [values] = extendedEvklid(a0, a1)

x0 = 1; y0 = 0;
x1 = 0; y1 = 1;

while a1 > 1
    %fprintf('\n%d-%d*%d = %d\n');
    q = a0/a1;
    q = floor(q);
    a = a0 - q*a1;
    %fprintf('\n%d-%d*%d = %d\n', a0, q, a1, a);
    x = x0 - q*x1;
    y = y0 - q*y1;
    a0 = a1;
    a1 = a;
    x0 = x1;
    x1 = x;
    y0 = y1;
    y1 = y;
end

values{1} = a1;        %nod
values{2} = x1;        %x, k
values{3} = y1;        %y, d
return;