/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Listener.cpp]: Header file for Listener feature.
*/

#ifndef CPP_BABEL_2020_LISTENER_HPP
#define CPP_BABEL_2020_LISTENER_HPP

#include "ASocket.hpp"
#include "AThread.hpp"
#include "ClientSocket.hpp"
#include "ClientsList.hpp"

namespace BabelServer {

    class Listener : public BabelNetwork::ASocket {
        /* <- Constructor - Destructor -> */
    public:
        /* <- Public Methods -> */
    public:
        explicit Listener(
            const std::string &address,
            const std::string &port,
            BabelUtils::Logger &logger
        ) : BabelNetwork::ASocket(address, port, logger) {}


        std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> getClientList()
        {
            _clientsList.lock();
            auto list = _clientsList.getClients();
            _clientsList.unlock();
            return list;
        };


        /* <- Attributes -> */
    protected:
        ClientsList _clientsList;
    };
}


#endif //CPP_BABEL_2020LISTENER_HPP
