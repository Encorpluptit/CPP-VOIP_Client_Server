/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 8/22/20).
** File description:
** [ClientCore.cpp]: Source file for ClientCore feature.
*/

#include <iostream>
#include "ClientCore.hpp"
#include "mainwindow.hpp"
#include "NetworkInfos.hpp"

using namespace BabelClient;

ClientCore::ClientCore(int ac, char **av, NetworkClientSocket &client)
    : _logger(BabelUtils::Logger::ClientLog),
    app(ac, av),
    network(client),
    window(new MainWindow(nullptr, network))
{
    network.run();
}

ClientCore::~ClientCore()
{
    delete window;
}

int ClientCore::run()
{
    window->show();
    return (app.exec());
}