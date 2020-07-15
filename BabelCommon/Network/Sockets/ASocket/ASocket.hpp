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
        explicit ASocket(const NetworkInfos &networkInfos);

        ~ASocket() override = default;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] bool isReady() const;

        void setReady();

        [[nodiscard]] const NetworkInfos &getNetworkInfos() const;

        /* <- Operators -> */
    public:
        bool operator==(const NetworkInfos &other) const;

        bool operator==(const ASocket &other) const;

        /* <- Attributes -> */
    protected:
        const NetworkInfos &_networkInfos;
        bool _ready = false;
    };

}

#endif /* CPP_BABEL_2020_ASOCKET_HPP */
