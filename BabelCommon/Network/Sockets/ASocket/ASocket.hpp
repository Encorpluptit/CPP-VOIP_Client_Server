/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.hpp]: Header file for ASocket feature.
*/

#ifndef CPP_BABEL_2020_ASOCKET_HPP
#define CPP_BABEL_2020_ASOCKET_HPP

#include "ISocket.hpp"

namespace BabelNetwork {

    class ASocket : virtual public ISocket {

        /* <- Constructor - Destructor -> */
    public:
        ASocket() = default;

        ~ASocket() override = default;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] bool isConnected() const;

        void setConnected(bool connected);

        /* <- Attributes -> */
    protected:
        bool _connected = false;
    };

}

#endif /* CPP_BABEL_2020_ASOCKET_HPP */
