/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <QApplication>
#include "mainwindow.hpp"
#include <iostream>

int main(int ac, char **av)
{
    QApplication app(ac, av);
    MainWindow w;

    w.adress(av[1], std::stoi(av[2]));
    w.show();

    return app.exec();
}
