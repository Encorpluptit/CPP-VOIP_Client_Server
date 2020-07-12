/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ISocket.hpp]: Header file for ISocket feature.
*/

#ifndef CPP_BABEL_2020_ISOCKET_HPP
#define CPP_BABEL_2020_ISOCKET_HPP

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
        ISocket() = default;

        virtual ~ISocket() = 0;

        /* <- Methods -> */
    public:
        [[nodiscard]] virtual bool connect() = 0;

        virtual void disconnect() = 0;

        [[nodiscard]] virtual bool isAvailable() const = 0;

    };

}

#endif /* CPP_BABEL_2020_ISOCKET_HPP */
