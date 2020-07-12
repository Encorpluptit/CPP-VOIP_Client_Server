/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/9/20).
** File description:
** [LoggerError.hpp]: Header file for LoggerError feature.
*/

#ifndef CPP_BABEL_2020_LOGGERERROR_HPP
#define CPP_BABEL_2020_LOGGERERROR_HPP

#include <exception>
#include <string>

namespace BabelUtils {
    class LoggerError : public std::exception {
    public:
        explicit LoggerError(std::string msg);

        [[nodiscard]] char const *what() const noexcept override;

    private:
        std::string _msg;
    };

}

#endif /* CPP_BABEL_2020_LOGGERERROR_HPP */
