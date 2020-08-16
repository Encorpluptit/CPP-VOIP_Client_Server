/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [UserResponse.cpp]: Source file for UserResponse feature.
*/

#include "UserResponse.hpp"
#include "StringFormat.tpp"
#include "NetworkError.hpp"

using namespace BabelNetwork;

UserResponse::UserResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse)
{
//    _header._dataInfosSize = headerResponse._dataInfosSize;
}

bool BabelNetwork::UserResponse::isOk() noexcept
{
    return _header._code == UserResponse::ResponseCode::ConnectionOk;
}

void BabelNetwork::UserResponse::setOk() noexcept
{
    _header._code = UserResponse::ResponseCode::ConnectionOk;
}

std::shared_ptr<AResponse> UserResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<UserResponse>(*this);
}

char *UserResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *UserResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

bool UserResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool UserResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool UserResponse::decode_data_infos() noexcept
{
    memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool UserResponse::decode_data() noexcept
{
    memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

char *UserResponse::getDataByte() noexcept
{
    return _data_byte;
}

size_t UserResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t UserResponse::getMaxResponseSize() const noexcept
{
    return MaxResponseSize;
}

size_t UserResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string UserResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string UserResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}

const std::string &UserResponse::getDescription() const noexcept
{
    return _description;
}

UserResponse::UserResponse(const std::string &login, const std::string &password)
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

