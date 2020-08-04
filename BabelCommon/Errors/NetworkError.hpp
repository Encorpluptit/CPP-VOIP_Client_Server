/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/4/20).
** File description:
** [NetworkError.hpp]: Header file for NetworkError feature.
*/

#ifndef CPP_BABEL_2020_NETWORKERROR_HPP
#define CPP_BABEL_2020_NETWORKERROR_HPP

#include "BabelError.hpp"

namespace BabelErrors {
    class NetworkError : virtual public BabelError {
        /* <- Constructor - Destructor -> */
    public:
        explicit NetworkError(std::string const &msg) : BabelError(msg) {}
    };
}



#endif /* CPP_BABEL_2020_NETWORKERROR_HPP */
