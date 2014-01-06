tablePC(X):-pc(X), ontable(X).
notebookPC(X):- pc(X),portable(X).
tabletPC(X):- pc(X),portable(X),touchscreen(X).
pc(c1).
pc(c2).
pc(c3).

ontable(c1).

portable(c2).
portable(c3).

touchscreen(c3).

owner(sergey,c1).
owner(sergey,c2).
owner(alex,c3).

