#ifndef WRAP_H
#define WRAP_H

#include <QGraphicsView>
#include <QPoint>
#include "figurefactory.h"
#include <QImage>
#include <QPainter>


class Wrap
{
public:
    Wrap();
    void drawCircle(int x, int y, int r, int color, bool paintedOver);
    void drawQuadrate(int x, int y, int h, int color, bool paintedOver);
    void drawRectangle(int x, int y, int h, int w, int color, bool paintedOver);
    void changeSize(int x, int y, int h, int w);

    void saveToJpg();
    void openImage();

private:
    FigureFactory storage;
    Figure *figure;
};

#endif // WRAP_H
