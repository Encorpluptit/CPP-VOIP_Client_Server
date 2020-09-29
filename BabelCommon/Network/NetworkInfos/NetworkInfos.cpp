/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/12/20).
** File description:
** [NetworkInfos.cpp]: Source file for NetworkInfos feature.
*/

#include <utility>
#include <charconv>
#include <boost/lexical_cast.hpp>
#include "NetworkInfos.hpp"
#include "NetworkError.hpp"

using namespace BabelNetwork;

NetworkInfos::NetworkInfos(std::string ip, const std::string &port)
    : _ip(std::move(ip)), _port_str(port), _port(parsePort(port))
{
    if (_port < 5000)
        throw BabelErrors::NetworkError("Port Reserved");
}

uint16_t NetworkInfos::parsePort(const std::string &port)
{
    uint16_t _parsed_port = 0;
    auto parsed = std::from_chars(port.c_str(), port.end().base(), _parsed_port);

    if (parsed.ec == std::errc::invalid_argument
        || parsed.ec == std::errc::result_out_of_range
        || parsed.ptr != port.end().base())
        throw BabelErrors::NetworkError("Could not parse port");
    return _parsed_port;
}

namespace BabelNetwork {
    std::ostream &operator<<(std::ostream &os, const NetworkInfos &connection)
    {
        os << "Connexion at " << connection.getIp() << " address and port " << std::to_string(connection.getPort());
        return os;
    }
}

uint16_t NetworkInfos::getPort() const
{
    return _port;
}

void NetworkInfos::setPort(uint16_t port)
{
    _port = port;
}

const std::string &NetworkInfos::getIp() const
{
    return _ip;
}

void NetworkInfos::setIp(const std::string &ip)
{
    _ip = ip;
}

bool NetworkInfos::operator==(const NetworkInfos &other) const
{
    return this->getPort() == other.getPort() && this->getIp() == other.getIp();
}

const std::string &NetworkInfos::getPortStr() const
{
    return _port_str;
}
