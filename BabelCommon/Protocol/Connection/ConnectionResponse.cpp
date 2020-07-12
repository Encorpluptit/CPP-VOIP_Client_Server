/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Source file for ConnectionResponse feature.
*/

#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

ConnectionResponse::ConnectionResponse()
    : _description("Connection between server and client")
{}

ConnectionResponse::ConnectionResponse(const ResponseHeader *response, const char *data)
    : AResponse(response, data),
      _description("Connection between server and client")
{}

bool BabelNetwork::ConnectionResponse::isOk()
{
    return _code == IResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::ConnectionResponse::setOk()
{
    _code = IResponse::ResponseCode::ConnectionOk;
}
