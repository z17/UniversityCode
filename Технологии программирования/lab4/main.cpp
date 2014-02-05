#include "dialog.h"
#include <QApplication>
#include <QBrush>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setMaximumWidth(950);
    w.setMaximumHeight(950);
    w.showMaximized();

    return a.exec();
}
