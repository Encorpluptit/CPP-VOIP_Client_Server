/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/19/20).
** File description:
** [ResponseError.hpp]: Header file for ResponseErrorpp feature.
*/

#ifndef CPP_BABEL_2020_RESPONSEERROR_HPP
#define CPP_BABEL_2020_RESPONSEERROR_HPP

#include "NetworkError.hpp"

namespace BabelErrors {
    class ResponseError : public NetworkError {
        /* <- Constructor - Destructor -> */
    public:
        explicit ResponseError(std::string const &msg) : NetworkError(msg) {}
    };

    class UserResponse : public ResponseError {
        /* <- Constructor - Destructor -> */
    public:
        explicit UserResponse(std::string const &msg) : ResponseError(msg) {}
    };

    class CallResponse : public ResponseError {
        /* <- Constructor - Destructor -> */
    public:
        explicit CallResponse(std::string const &msg) : ResponseError(msg) {}
    };

    class FriendResponse : public ResponseError {
        /* <- Constructor - Destructor -> */
    public:
        explicit FriendResponse(std::string const &msg) : ResponseError(msg) {}
    };

    class MessageResponse : public ResponseError {
        /* <- Constructor - Destructor -> */
    public:
        explicit MessageResponse(std::string const &msg) : ResponseError(msg) {}
    };
}


#endif /* CPP_BABEL_2020_RESPONSEERROR_HPP */
