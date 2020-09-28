/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/6/20).
** File description:
** [Listener.cpp]: Header file for Listener feature.
*/

#ifndef CPP_BABEL_2020_LISTENER_HPP
#define CPP_BABEL_2020_LISTENER_HPP

#include "ASocket.hpp"
#include "ClientSocket.hpp"
#include "ClientsList.hpp"

namespace BabelServer {

    class Listener : virtual public BabelNetwork::ASocket, virtual public std::mutex {
        /* <- Constructor - Destructor -> */
    public:
        /* <- Public Methods -> */
    public:
        ClientsList getClientList()
        {
            lock();
            auto lol = ClientsList(_clientsList);
            unlock();
            return lol;
        };

        /* <- Attributes -> */
    protected:
        ClientsList _clientsList;
    };
}


#endif //CPP_BABEL_2020LISTENER_HPP
