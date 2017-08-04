#include "global.h"
#include "mainwindow.h"
#include <QApplication>

int WIDTH;
int HEIGHT;
int CURRENT_SIGN = 1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
