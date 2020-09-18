#include "mainwindow.h"

#include <QApplication>

#include <iostream>

int lol(int argc, char *argv[])
{
    int lul = 0;

    QApplication a(lul, nullptr);
    MainWindow w;
    w.show();
    return a.exec();
}

int main(int argc, char *argv[])
{
    lol(argc, argv);
    std::cout << "coucou" << std::endl;
    return 0;
}
