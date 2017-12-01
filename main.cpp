/*
    Fatih (6251581), Javi (), Lesik (6081100), Kelvin Tsang (5428328)

    Milestone 1

*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.game->setUniverseSize(3);
    return a.exec();
}
