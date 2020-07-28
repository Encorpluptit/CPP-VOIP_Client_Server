/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/28/20).
** File description:
** [AsioSocket.cpp]: Source file for AsioSocket feature.
*/

#include "AsioSocket.hpp"

using namespace BabelNetwork;

AsioSocket::AsioSocket(const NetworkInfos &networkInfos, io_context &context)
    : ASocket(networkInfos), _context(context)
{

}

void AsioSocket::stop()
{
    _context.stop();
};
