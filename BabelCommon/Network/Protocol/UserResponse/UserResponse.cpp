/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [UserResponse.cpp]: Source file for UserResponse feature.
*/

#include "UserResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

UserResponse::UserResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse) {}

UserResponse::UserResponse(const std::string &login, const std::string &password)
    : AResponse()
{
    _header._responseType = User;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setPassword(password))
        throw BabelErrors::UserResponse("login or password too long");
}

bool UserResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool UserResponse::setPassword(const std::string &password) noexcept
{
    if (password.size() > MaxDataSize::Password)
        return false;
    strcat(_data.password, password.c_str());
    _dataInfos._passwordSize = password.size();
    return true;
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

bool BabelNetwork::UserResponse::isOk() noexcept
{
    return _header._code == UserResponse::ResponseCode::LoginOk
        || _header._code == UserResponse::ResponseCode::AccountCreated
        || _header._code == UserResponse::ResponseCode::AccountDeleted;
}

std::shared_ptr<AResponse> UserResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<UserResponse>(*this);
}

char *UserResponse::getDataByte() noexcept
{
    return _data_byte;
}

char *UserResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *UserResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

size_t UserResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
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
