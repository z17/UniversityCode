table(X):-pc(X), ontable(X).
notebook(X):- pc(X),portable(X),not(touchscreen(X)).
tablet(X):- pc(X),portable(X),touchscreen(X).
havePC(X):-man(X,Y), pc(Y).
windows(X):- oc(X,win7);oc(X,win8);oc(X,winxp).
linux(X):- oc(X,linux).

pc(c1).
pc(c2).
pc(c3).
pc(c4).
pc(c5).
oc(c1,win7).
oc(c2,win7).
oc(c3,win8).
oc(c4,linux).
oc(c5,winxp).
ontable(c1).
portable(c2).
portable(c3).
touchscreen(c3).
man(sergey, c1).
man(sergey, c4).
man(alex, c2).
man(igor, c5).
