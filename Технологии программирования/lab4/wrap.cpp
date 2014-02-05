#include "wrap.h"


Wrap::Wrap()
{

}

void Wrap::drawCircle(int x, int y, int r, int color, bool paintedOver)
{
    Circle *figure = new Circle(x, y, r, color, paintedOver);
    storage.addFigure(figure);
}

void Wrap::drawQuadrate(int x, int y, int h, int color, bool paintedOver)
{
    Quadrate *figure = new Quadrate(x, y, h, color, paintedOver);
    storage.addFigure(figure);
}

void Wrap::drawRectangle(int x, int y, int h, int  w, int color, bool paintedOver)
{
    Rectangle *figure = new Rectangle(x, y, h, w, color, paintedOver);
    storage.addFigure(figure);
}

void Wrap::changeSize(int x, int y, int h, int w)
{
    for (int i = storage.getSize() - 1; i >= 0 ; i--)
    {
        Figure *f = storage.getFigure(i);
        int x1 = f->getX();
        int y1 = f->getY();
        int x2, y2;
        switch (f->getType())
        {
        case 0:
            x1 = x1 + f->getH()/2;
            y1 = y1 + f->getH()/2;
            if ( (x1 - x)*(x1 - x) + (y1 - y)*(y1 - y) < (f->getH()/2)*(f->getH()/2) )
            {
                f->changeSize(h, h);
            }
            break;
        case 1:
            x2 = x1 + f->getH();
            y2 = y1 + f->getH();
            if (x>=x1 && y>=y1 && x<=x2 && y<=y2)
            {
               f->changeSize(h, h);
            }
            break;
        case 2:
            x2 = x1 + f->getH();
            y2 = y1 + f->getW();
            if (x>=x1 && y>=y1 && x<=x2 && y<=y2)
            {
               f->changeSize(h, w);
            }
            break;
        }
    }
}

void Wrap::saveToJpg()
{
    QImage image(global::scene->width(), global::scene->height(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    global::scene->render(&painter);
    image.save("out.jpg");
}

void Wrap::openImage()
{
    global::scene->addPixmap(QPixmap("out.jpg"));
}
