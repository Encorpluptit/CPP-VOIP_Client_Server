/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/8/20).
** File description:
** [main.cpp]: Main program entry.
*/

#include <iostream>
//#include <QApplication>
#include "mainwindow.hpp"

/*int main(int ac, char **av)
{
    QApplication app(ac, av);
    MainWindow w;
    BabelNetwork::NetworkInfos nwi(av[1], av[2]);

    w.adress(nwi.getIp(), nwi.getPort());
    w.show();

    return app.exec();
}
*/

int main(int ac, char **av)
{
    if (ac != 3)
        return (84);
    ClientCore client(ac, av);

    //client.loop();
    return (0);
}