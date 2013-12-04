#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPen>
#include <QPoint>
#include <QMouseEvent>



MainWindow::MainWindow(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::MainWindow)
{
    figures = new QGraphicsScene;
    figures->setSceneRect(0, 0, 800, 600);
    this->setScene(figures);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
 {
    QPen pen1(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPen pen2(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    QPoint p1 = this->mapFromGlobal(QCursor::pos());
    QPointF p2 = this->mapToScene(p1);

    int x = p2.x();
    int y = p2.y();

    if (event->button() == Qt::LeftButton)
    {
        figures->addEllipse(x,y,100,100,pen1);
    }

    if (event->button() == Qt::RightButton)
    {
        figures->addRect(x,y,100,100,pen2);
    }

 }
