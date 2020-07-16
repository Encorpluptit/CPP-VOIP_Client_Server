/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ISocket.hpp]: Header file for ISocket feature.
*/

#ifndef CPP_BABEL_2020_ISOCKET_HPP
#define CPP_BABEL_2020_ISOCKET_HPP

#include "NetworkInfos.hpp"
#include "AResponse.hpp"

namespace BabelNetwork {
    class ISocket {
        /* <- Class Enum -> */
    public:
        enum SocketType {
            TCP,
            UDP,
            QT
        };

        /* <- Constructor - Destructor -> */
    public:
        virtual ~ISocket() = 0;

        /* <- Methods -> */
    public:
        virtual void start() = 0;

        virtual void stop() = 0;

        [[nodiscard]] virtual bool sendResponse(const AResponse &response) = 0;

    };

}

#endif /* CPP_BABEL_2020_ISOCKET_HPP */
