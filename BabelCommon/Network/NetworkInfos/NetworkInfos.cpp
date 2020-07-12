/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) $USER_NAME.capitalize() on 7/12/20).
** File description:
** [NetworkInfos.cpp]: Source file for NetworkInfos feature.
*/

#include <utility>
#include <boost/lexical_cast.hpp>
#include "NetworkInfos.hpp"

BabelNetwork::NetworkInfos::NetworkInfos(std::string ip, const std::string& port)
    : _ip(std::move(ip))
{
    _port = boost::lexical_cast<uint16_t>(port);
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::NetworkInfos &connection)
{
    os << "Running at " << connection.getIp() << " address and port " << std::to_string(connection.getPort());
    return os;
}

uint16_t BabelNetwork::NetworkInfos::getPort() const
{
    return _port;
}

void BabelNetwork::NetworkInfos::setPort(uint16_t port)
{
    _port = port;
}

const std::string &BabelNetwork::NetworkInfos::getIp() const
{
    return _ip;
}

void BabelNetwork::NetworkInfos::setIp(const std::string &ip)
{
    _ip = ip;
}
