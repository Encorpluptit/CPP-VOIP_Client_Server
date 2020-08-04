/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/4/20).
** File description:
** [BabelError.hpp]: Header file for BabelError feature.
*/

#ifndef CPP_BABEL_2020_BABELERROR_HPP
#define CPP_BABEL_2020_BABELERROR_HPP

#include <string>

namespace BabelErrors {

    class BabelError : public std::exception {
        /* <- Constructor - Destructor -> */
    public:
        explicit BabelError(std::string const &msg) : _msg(msg) {};

        /* <- Public Methods -> */
    public:
        char const *what() const noexcept override { return _msg.c_str(); };

    private:
        std::string _msg;
    };
}

#endif /* CPP_BABEL_2020_BABELERROR_HPP */
