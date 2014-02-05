#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

#include "figure.h"
#include <fstream>
#include <vector>

class FigureFactory
{
public:
    FigureFactory();
    void addFigure(Figure *figure);
    Figure* getFigure(int i) const;
    int getSize() const;
    ~FigureFactory();

private:
    std::vector <Figure*> storage;
};

#endif // FIGUREFACTORY_H
