/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/9/20).
** File description:
** [LoggerError.cpp]: Source file for LoggerError feature.
*/

#include "LoggerError.hpp"

BabelUtils::LoggerError::LoggerError(const std::string &msg)
    : _msg(msg)
{

}

char const *BabelUtils::LoggerError::what() const noexcept
{
    return exception::what();
}
