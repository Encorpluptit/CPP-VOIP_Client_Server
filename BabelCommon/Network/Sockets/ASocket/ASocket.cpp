/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.cpp]: Source file for ASocket feature.
*/

#include "ASocket.hpp"

BabelNetwork::ASocket::ASocket(const BabelNetwork::NetworkInfos &networkInfos)
    : _networkInfos(networkInfos)
{}

bool BabelNetwork::ASocket::isReady() const
{
    return _ready;
}

void BabelNetwork::ASocket::setReady()
{
    _ready = true;
}
