#ifndef FIGURE_H
#define FIGURE_H

#include "global.h"
#include <QGraphicsItem>
#include <QTransform>

class Figure
{
public:
   virtual int getType() = 0;
   virtual void changeSize( int _h, int _w) = 0;
   virtual int getX() const = 0;
   virtual int getY() const  = 0;
   virtual int getH() const = 0;
   virtual int getW() const  = 0;

    int x, y, h, w, color;
   bool paintedOver;
};

class Circle : public Figure
{
public:
    Circle();
    Circle(int _x, int _y, int _r, int _color, bool _paintedOver);
    void changeSize( int _h, int _w);
    int getType();
    int getX() const;
    int getY() const;
    int getH() const;
    int getW() const;
};

class Quadrate : public Figure
{
public:
    Quadrate();
    Quadrate(int _x, int _y, int _h, int _color, bool _paintedOver);
    void changeSize(int _h, int _w);
    int getType();
    int getX() const;
    int getY() const;
    int getH() const;
    int getW() const;
};

class Rectangle : public Figure
{
public:
    Rectangle();
    Rectangle(int _x, int _y, int _h, int _w, int _color, bool _paintedOver);
    void changeSize(int _h, int _w);
    int getType();
    int getX() const;
    int getY() const;
    int getH() const;
    int getW() const;
};

#endif // FIGURE_H
