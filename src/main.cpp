#include "kometa.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kometa kometaWidget;
    kometaWidget.show();
    return a.exec();
}
