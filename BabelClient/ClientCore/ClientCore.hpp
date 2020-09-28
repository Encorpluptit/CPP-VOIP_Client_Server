/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCore.hpp]: Header file for ClientCore feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCORE_HPP
#define CPP_BABEL_2020_CLIENTCORE_HPP

#include <QApplication>
#include "NetworkError.hpp"
#include "AResponse.hpp"
#include "mainwindow.hpp"
#include "Logger.hpp"

namespace BabelClient {

    class ClientCore {
        /* <- Constructor - Destructor -> */
    public:
        ClientCore(int ac, char **av, NetworkClientSocket &network);

        ~ClientCore();


        int run();

        /* <- Public Attributs -> */
    private:
        BabelUtils::Logger _logger;
        QApplication app;
        NetworkClientSocket &network;
        MainWindow *window;
    };
}

#endif /* CPP_BABEL_2020_CLIENTCORE_HPP */
