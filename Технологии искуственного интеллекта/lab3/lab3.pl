weapon(sword).
weapon(bow).
weapon(crossbow).
weapon(spear).
weapon(banner).

instrument(knife).
instrument(hammer).

man(bob, sword).
man(rob, knife).
man(nik, crossbow).
man(ivan, crossbow).
man(mark, hammer).
man(richard, bow).

soldier(X):-man(X, Y),weapon(Y).
attendant(X):-man(X, Y),instrument(Y).



























































































