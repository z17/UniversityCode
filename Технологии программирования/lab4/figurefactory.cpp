#include "figurefactory.h"

FigureFactory::FigureFactory()
{
}

void FigureFactory::addFigure(Figure *figure)
{
    storage.push_back(figure);
}

Figure* FigureFactory::getFigure(int i) const
{
    return storage[i];
}

int FigureFactory::getSize() const
{
    return storage.size();
}

FigureFactory::~FigureFactory()
{
    for(int i = 0; i < storage.size(); i++)
    {
        delete storage[i];
    }
}
