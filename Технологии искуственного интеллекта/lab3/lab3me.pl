tablePC(X):-pc(X), ontable(X).
notebookPC(X):- pc(X),portable(X),untouchscreen(X).
tabletPC(X):- pc(X),portable(X),touchscreen(X).
havePC(X):-man(X,Y), pc(Y).

pc(c1).
pc(c2).
pc(c3).

ontable(c1).

portable(c2).
portable(c3).

untouchscreen(c2).
touchscreen(c3).

man(sergey, c1).
man(alex, c2).
man(igor, c5).

