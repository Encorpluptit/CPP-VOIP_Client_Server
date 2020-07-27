/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Source file for ConnectionResponse feature.
*/

#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

ConnectionResponse::ConnectionResponse(const ResponseHeader *response)
    : AResponse(response)
{}

bool BabelNetwork::ConnectionResponse::isOk()
{
    return _header.returnCode == IResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::ConnectionResponse::setOk()
{
    _header.returnCode = IResponse::ResponseCode::ConnectionOk;
}

bool ConnectionResponse::decode_data()
{
    // TODO: Implement
    return true;
}

const char *ConnectionResponse::getBodyData() const
{
    return _bodyData;
}

const std::string &ConnectionResponse::getDescription() const
{
    return _description;
}

size_t ConnectionResponse::getResponseDataSize()
{
    return sizeof(_bodyData);
}


