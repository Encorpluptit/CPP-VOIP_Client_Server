/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/28/20).
** File description:
** [AsioSocket.cpp]: Source file for AsioSocket feature.
*/

#include "AsioSocket.hpp"

using namespace BabelNetwork;

AsioSocket::AsioSocket(const std::string &address, const std::string &port, io_context &context)
    : ASocket(address, port), _context(context)
{

}

void AsioSocket::stop()
{
    _context.stop();
};
