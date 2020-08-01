/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Source file for ConnectionResponse feature.
*/

#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

ConnectionResponse::ConnectionResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse)
{
    _header.responseType = Connection;
}

bool BabelNetwork::ConnectionResponse::isOk() noexcept
{
    return _header.returnCode == AResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::ConnectionResponse::setOk() noexcept
{
    _header.returnCode = AResponse::ResponseCode::ConnectionOk;
}

bool ConnectionResponse::decode_data() noexcept
{
    memcpy(&_data, _body_data, _data_size);
    return true;
}

char *ConnectionResponse::getBodyData() noexcept
{
    return _body_data;
}

const std::string &ConnectionResponse::getDescription() const noexcept
{
    return _description;
}
//
//size_t ConnectionResponse::getDataSize() noexcept
//{
//    return sizeof(ConnectionData);
//}

bool ConnectionResponse::encode_data() noexcept
{
    memcpy(_body_data, &_data, _data_size);
    return true;
}

std::shared_ptr<AResponse> ConnectionResponse::getResponse() const
{
    return std::make_shared<ConnectionResponse>(*this);
}

char *ConnectionResponse::getBody() noexcept
{
    return reinterpret_cast<char *>(&_data);
}


