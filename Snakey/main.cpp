#include "mainwindow.h"
#include "menuwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow M;
    M.show();
    return a.exec();
}
