/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCore.hpp]: Header file for ClientCore feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCORE_HPP
#define CPP_BABEL_2020_CLIENTCORE_HPP

#include "AsioClientSocket.hpp"
#include "boost/shared_ptr.hpp"
#include "SharedPtr.hpp"

namespace BabelClient {

    class ClientCore final : virtual public BabelUtils::ARunnable {
        /* <- Constructor - Destructor -> */
    public:
        ClientCore(int ac, char **av);

        ~ClientCore() final;

        /* <- Public Methods -> */
    public:
        void start() final;

        void stop() final;

        void run();

        /* <- Private Methods -> */
    private:
        void init();

        void initSocket(int ac, char **av);

        /* <- Getters / Setters -> */
    public:
        BabelUtils::Logger _logger;
        SharedPtr<BabelNetwork::ClientSocket> _socket;
//        boost::shared_ptr<BabelNetwork::ClientSocket> _socket;
    };

}

#endif /* CPP_BABEL_2020_CLIENTCORE_HPP */
