#include "dialog.h"
#include "ui_dialog.h"

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QWheelEvent>
#include <QPalette>
#include <QColor>

Dialog::Dialog()
{
    global::scene = new QGraphicsScene;
    global::scene->setSceneRect(0, 0, 900, 800);
    global::scene->setBackgroundBrush(QBrush(Qt::white));

    view = new QGraphicsView;
    view->setScene(global::scene);
    QColor col(255, 255, 255);
    QPalette palet(col);
    this->setPalette(palet);
    button1 = new QRadioButton("Circle");
    button2 = new QRadioButton("Quadrate");
    button3 = new QRadioButton("Rectangle");
    QGroupBox *group1 = new QGroupBox("Shape:");

    QVBoxLayout *vert1 = new QVBoxLayout;
    vert1->addWidget(button1);
    vert1->addWidget(button2);
    vert1->addWidget(button3);

    buttonColor1 = new QRadioButton("Red");
    buttonColor2 = new QRadioButton("Blue");
    buttonColor3 = new QRadioButton("Black");
    QGroupBox *group2 = new QGroupBox("Color:");

    // по умолчанию чёрный цвет
    buttonColor3->setEnabled(true);
    buttonColor3->click();

    QVBoxLayout *vert2 = new QVBoxLayout;
    vert2->addWidget(buttonColor1);
    vert2->addWidget(buttonColor2);
    vert2->addWidget(buttonColor3);

    QPushButton *button7 = new QPushButton("Open");
    QPushButton *button8 = new QPushButton("Save");
    QVBoxLayout *vert3 = new QVBoxLayout;
    QGroupBox *group3 = new QGroupBox("File:");

    vert3->addWidget(button7);
    vert3->addWidget(button8);

    QHBoxLayout *vert4 = new QHBoxLayout;
    group1->setLayout(vert1);
    group2->setLayout(vert2);
    group3->setLayout(vert3);

    buttonPaintedOn = new QRadioButton("Painted Over");
    buttonPaintedOff = new QRadioButton("Not Painted Over");
    QVBoxLayout *vert6 = new QVBoxLayout;
    QGroupBox *group5 = new QGroupBox("Fill:");
    vert6->addWidget(buttonPaintedOn);
    vert6->addWidget(buttonPaintedOff);
    group5->setLayout(vert6);
    buttonPaintedOn->click();

    line1 = new QLineEdit("10");
    line2 = new QLineEdit("25");
    QVBoxLayout *vert7 = new QVBoxLayout;
    QGroupBox *group6 = new QGroupBox("Change size:");
    vert7->addWidget(line1);
    vert7->addWidget(line2);
    group6->setLayout(vert7);

    QVBoxLayout *vert5 = new QVBoxLayout;
    vert4->setSpacing(50);

    vert4->addWidget(group3);
    vert4->addWidget(group5);
    vert4->addWidget(group1);
    vert4->addWidget(group6);
    vert4->addWidget(group2);

    vert5->addLayout(vert4);
    vert5->addWidget(view);
    this->setLayout(vert5);

    line2->setEnabled(false);
    connect( button1, SIGNAL(clicked(bool)), this, SLOT(setLineStateFalse()) );
    connect( button2, SIGNAL(clicked(bool)), this, SLOT(setLineStateFalse()) );
    connect( button3, SIGNAL(clicked(bool)), this, SLOT(setLineStateTrue()) );
    connect( button8, SIGNAL(clicked(bool)), this, SLOT(saveImage()) );
    connect( button7, SIGNAL(clicked(bool)), this, SLOT(openImage()) );
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    QPoint p1 = view->mapFromGlobal(QCursor::pos());
    QPointF p2 = view->mapToScene(p1);

    // определяем цвет
    if (buttonColor1->isChecked())
        _color = 0;
    if (buttonColor2->isChecked())
        _color = 1;
    if (buttonColor3->isChecked())
        _color = 2;

    // заливка
    if (buttonPaintedOn->isChecked())
        fl = true;
    else
        fl = false;

    // размеры
    sizeHeight = line1->text().toInt();
    sizeWeight = line2->text().toInt();

    if (event->button() == Qt::LeftButton)
    {
        if (button1->isChecked())
            wrap.drawCircle(p2.x(), p2.y(), sizeHeight, _color, fl);

         if (button2->isChecked())
            wrap.drawQuadrate(p2.x(), p2.y(), sizeHeight, _color, fl);

         if (button3->isChecked())
            wrap.drawRectangle(p2.x(), p2.y(), sizeHeight, sizeWeight, _color, fl);
    }

    if (event->button() == Qt::RightButton)
    {
        wrap.changeSize(p2.x(), p2.y(), sizeHeight, sizeWeight);
    }

}

void Dialog::setLineStateFalse()
{
    line2->setEnabled(false);
}

void Dialog::setLineStateTrue()
{
    line2->setEnabled(true);
}

void Dialog::saveImage()
{
    wrap.saveToJpg();
}

void Dialog::openImage()
{
    wrap.openImage();
}

Dialog::~Dialog()
{}
