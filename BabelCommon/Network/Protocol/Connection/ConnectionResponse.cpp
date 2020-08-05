/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Source file for ConnectionResponse feature.
*/

//#include <boost/shared_ptr.hpp>
#include "ConnectionResponse.hpp"
#include "StringFormat.tpp"
#include "NetworkError.hpp"

using namespace BabelNetwork;

ConnectionResponse::ConnectionResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse)
{
//    _header._dataInfosSize = headerResponse._dataInfosSize;
}

bool BabelNetwork::ConnectionResponse::isOk() noexcept
{
    return _header._code == AResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::ConnectionResponse::setOk() noexcept
{
    _header._code = AResponse::ResponseCode::ConnectionOk;
}

std::shared_ptr<AResponse> ConnectionResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<ConnectionResponse>(*this);
}

char *ConnectionResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *ConnectionResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

bool ConnectionResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool ConnectionResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool ConnectionResponse::decode_data_infos() noexcept
{
    memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool ConnectionResponse::decode_data() noexcept
{
    memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

char *ConnectionResponse::getDataByte() noexcept
{
    return _data_byte;
}

size_t ConnectionResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t ConnectionResponse::getMaxResponseSize() const noexcept
{
    return MaxResponseSize;
}

size_t ConnectionResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string ConnectionResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string ConnectionResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}

const std::string &ConnectionResponse::getDescription() const noexcept
{
    return _description;
}

ConnectionResponse::ConnectionResponse(const std::string &login, const std::string &password)
    : AResponse()
{
    _header._responseType = Connection;
    _header._dataInfosSize = DataInfosSize;
    if (login.size() > MaxDataSize::Login || password.size() > MaxDataSize::Password)
        throw BabelErrors::NetworkError("login or password too long");
    strcat(_data.login, login.c_str());
    strcat(_data.password, password.c_str());
    _dataInfos._loginSize = login.size();
    _dataInfos._passwordSize = password.size();
}

