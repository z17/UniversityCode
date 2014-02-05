#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPoint>
#include <QLineEdit>
#include "wrap.h"
#include <QRadioButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog();

    virtual void mousePressEvent(QMouseEvent *event);
    ~Dialog();

public slots:
    void setLineStateFalse();
    void setLineStateTrue();
    void saveImage();
    void openImage();

private:
    QGraphicsView *view;
    Wrap wrap;
    int x;
    int y;
    int _color;
    int sizeHeight, sizeWeight;
    bool fl;
    QRadioButton *button1, *button2, *button3;
    QRadioButton *buttonColor1, *buttonColor2, *buttonColor3;
    QRadioButton *buttonPaintedOn, *buttonPaintedOff;
    QRadioButton *button9, *button12, *button13, *button14;
    QLineEdit *line1, *line2;
};

#endif // DIALOG_H
