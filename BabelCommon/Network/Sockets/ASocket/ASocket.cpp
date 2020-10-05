/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [ASocket.cpp]: Source file for ASocket feature.
*/

#include "ASocket.hpp"

using namespace BabelNetwork;

BabelNetwork::ASocket::ASocket(
    const std::string &address,
    const std::string &port,
    BabelUtils::Logger &logger
)
    : _networkInfos(address, port),
      _logger(logger)
{

}

const NetworkInfos &ASocket::getNetworkInfos() const
{
    return _networkInfos;
}

bool BabelNetwork::ASocket::operator==(const BabelNetwork::NetworkInfos &other) const
{
    return this->getNetworkInfos() == other;
}

bool BabelNetwork::ASocket::operator==(const BabelNetwork::ASocket &other) const
{
    return this->getNetworkInfos() == other.getNetworkInfos();
}
