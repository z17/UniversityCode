#ifndef GLOBAL_H
#define GLOBAL_H

#include <QGraphicsScene>
#include <QBrush>
#include <QPen>


namespace global {
    extern QGraphicsScene *scene;
    extern QBrush *brush;
    extern QPen *pen;
    void setColor(int);
}

#endif // GLOBAL_H
