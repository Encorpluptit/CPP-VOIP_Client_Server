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

//    using ClientList = std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>>;

    class Listener : virtual public BabelNetwork::ASocket {
        /* <- Constructor - Destructor -> */
    public:
        /* <- Public Methods -> */
    public:
//        virtual std::vector<BabelUtils::SharedPtr<BabelNetwork::ClientSocket>> getClientList() = 0;

        virtual BabelNetwork::ClientList getClientList() = 0;

        /* <- Attributes -> */
    protected:
        // TODO: Client List here instead of Asio client list in AsioListener ?
        BabelUtils::SharedPtr<ClientsList> _clientsList;
    };
}


#endif //CPP_BABEL_2020LISTENER_HPP
