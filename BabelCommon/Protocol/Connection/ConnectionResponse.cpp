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
    _header.dataLength = headerResponse.dataLength;
}

bool BabelNetwork::ConnectionResponse::isOk() noexcept
{
    return _header.returnCode == AResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::ConnectionResponse::setOk() noexcept
{
    _header.returnCode = AResponse::ResponseCode::ConnectionOk;
}

const std::string &ConnectionResponse::getDescription() const noexcept
{
    return _description;
}

std::shared_ptr<AResponse> ConnectionResponse::getResponse() const
{
    return std::make_shared<ConnectionResponse>(*this);
}

char *ConnectionResponse::getBody() const noexcept
{
    return const_cast<char *>(_data_byte + ResponseHeaderSize);
}

bool ConnectionResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, ResponseHeaderSize);
    memcpy(_data_byte + ResponseHeaderSize, &_data, ResponseDataSize);
    return true;
}

bool ConnectionResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, ResponseHeaderSize);
    return true;
}

bool ConnectionResponse::decode_data() noexcept
{
    memcpy(&_data, _data_byte + ResponseHeaderSize, ResponseDataSize);
    return true;
}

char *ConnectionResponse::getDataByte() noexcept
{
    return _data_byte;
}

uint32_t ConnectionResponse::getResponseSize() const noexcept
{
    return ResponseHeaderSize + ResponseDataSize;
}

std::string ConnectionResponse::serialize_data() const
{
    std::string rt;

    rt +=  _data.login;
    rt += "|";
    rt += _data.password;
    return rt;
}