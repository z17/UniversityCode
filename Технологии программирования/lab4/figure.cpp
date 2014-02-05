#include "figure.h"
#include <QPointF>
#include <iostream>

Circle::Circle()
{
    x = 0;
    y = 0;
    h = 0;
}

Circle::Circle(int _x, int _y, int _r, int _color, bool _paintedOver)
{
    global::setColor(_color);
    if (_paintedOver)
        global::scene->addEllipse(_x, _y, _r, _r, *global::pen, *global::brush);
    else
        global::scene->addEllipse(_x, _y, _r, _r, *global::pen);

    x = _x;
    y = _y;
    h = _r;
    w = _r;
    color = _color;
    paintedOver = _paintedOver;
}

int Circle::getX() const
{
    return x;
}

int Circle::getY() const
{
    return y;
}

int Circle::getH() const
{
    return h;
}

int Circle::getW() const
{
    return w;
}

int Circle::getType()
{
    return 0;
}

void Circle::changeSize(int _h, int _w)
{
    QTransform transform;
    QGraphicsItem *item = global::scene->itemAt(x+h/2, y+h/2, transform);
    global::scene->removeItem(item);
    if (paintedOver)
        global::scene->addEllipse(x, y, _h, _h, *global::pen, *global::brush);
    else
        global::scene->addEllipse(x, y, _h, _h, *global::pen);

    h = _h;
    w = _h;
}

Quadrate::Quadrate()
{
    x = 0;
    y = 0;
    h = 0;
}

Quadrate::Quadrate(int _x, int _y, int _h, int _color, bool _paintedOver)
{
    global::setColor(_color);
    if (_paintedOver)
        global::scene->addRect(_x, _y, _h, _h, *global::pen, *global::brush);
    else
        global::scene->addRect(_x, _y, _h, _h, *global::pen);

    x = _x;
    y = _y;
    h = _h;
    color = _color;
    paintedOver = _paintedOver;
}

int Quadrate::getX() const
{
    return x;
}

int Quadrate::getY() const
{
    return y;
}

int Quadrate::getH() const
{
    return h;
}

int Quadrate::getW() const
{
    return w;
}

int Quadrate::getType()
{
    return 1;
}

void Quadrate::changeSize(int _h, int _w)
{

    QTransform transform;
    QGraphicsItem *item = global::scene->itemAt(x+1, y+1, transform);
    global::scene->removeItem(item);
    global::setColor(color);
    if (paintedOver)
        global::scene->addRect(x, y, _h, _h, *global::pen, *global::brush);
    else
        global::scene->addRect(x, y, _h, _h, *global::pen);

    h = _h;
    w =_h;

}

Rectangle::Rectangle()
{
    x = 0;
    y = 0;
    h = 5;
    w = 10;
}

Rectangle::Rectangle(int _x, int _y, int _h, int _w, int _color, bool _paintedOver)
{
    global::setColor(_color);
    if (_paintedOver)
        global::scene->addRect(_x, _y, _h, _w, *global::pen, *global::brush);
    else
        global::scene->addRect(_x, _y, _h, _w, *global::pen);

    x = _x;
    y = _y;
    h = _h;
    w = _w;
    color = _color;
    paintedOver = _paintedOver;
}

int Rectangle::getX() const
{
    return x;
}

int Rectangle::getY() const
{
    return y;
}

int Rectangle::getH() const
{
    return h;
}

int Rectangle::getW() const
{
    return w;
}

int Rectangle::getType()
{
    return 2;
}

void Rectangle::changeSize(int _h, int _w)
{
    QTransform transform;
    QGraphicsItem *item = global::scene->itemAt(x+1, y+1, transform);
    global::scene->removeItem(item);
    global::setColor(color);
    if (paintedOver)
        global::scene->addRect(x, y, _h, _w, *global::pen, *global::brush);
    else
        global::scene->addRect(x, y, _h, _w, *global::pen);

    h = _h;
    w =_w;
}
