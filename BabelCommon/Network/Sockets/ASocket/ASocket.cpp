/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.cpp]: Source file for ASocket feature.
*/

#include "ASocket.hpp"

bool BabelNetwork::ASocket::isConnected() const
{
    return _connected;
}

void BabelNetwork::ASocket::setConnected(bool connected)
{
    _connected = connected;
}
