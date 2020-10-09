/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/18/20).
** File description:
** [ClientError.cpp]: Source file for ClientError feature.
*/

#include "NetworkError.hpp"
#include "ClientSocket.hpp"

namespace BabelErrors {
    class ClientError : public NetworkError {
        /* <- Constructor - Destructor -> */
    public:
        explicit ClientError(std::string const &msg, BabelNetwork::ClientSocket &client) : NetworkError(msg),
                                                                                           _client(client) {}
        /* <- Method -> */
    public:
        [[nodiscard]] BabelNetwork::ClientSocket &getClient() const noexcept { return _client; };
    protected:
        BabelNetwork::ClientSocket &_client;
    };
}
