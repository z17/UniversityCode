#include "global.h"


QGraphicsScene *global::scene;
QBrush *global::brush;
QPen *global::pen;

void global::setColor(int color)
{
    switch (color)
    {
        case 0:
            pen = new QPen(Qt::red);
            brush = new QBrush(Qt::red);
            break;
        case 1:
            pen = new QPen(Qt::blue);
            brush = new QBrush(Qt::blue);
            break;
        case 2:
            pen = new QPen(Qt::black);
            brush = new QBrush(Qt::black);
            break;
       }
}
