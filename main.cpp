#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFontDatabase::addApplicationFont(":/fonts/resources/OpenSans-ExtraBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/OpenSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/resources/OpenSans-Light.ttf");
    w.show();
    return a.exec();
}
