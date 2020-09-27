/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/22/20).
** File description:
** [ClientCoreError.hpp]: Header file for ClientCoreErrorpp feature.
*/

#ifndef CPP_BABEL_2020_CLIENTCOREERROR_HPP
#define CPP_BABEL_2020_CLIENTCOREERROR_HPP

#include "BabelError.hpp"

namespace BabelClient {
    class ClientError : public BabelErrors::BabelError {
        /* <- Constructor - Destructor -> */
    public:
        explicit ClientError(std::string const &msg) : BabelErrors::BabelError(msg) {}
    };
}

#endif /* CPP_BABEL_2020_CLIENTCOREERROR_HPP */
