#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-ExtraBold.ttf");
    QFontDatabase::addApplicationFont(":/fonts/OpenSans-Regular.ttf");
    w.show();
    return a.exec();
}
