/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [UserResponse.cpp]: Source file for UserResponse feature.
*/

#include "UserResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

BabelNetwork::UserResponse::UserResponse(const ResponseHeader &headerResponse)
    : BabelNetwork::AResponse(headerResponse) {}

BabelNetwork::UserResponse::UserResponse(const std::string &login, const std::string &password)
    : BabelNetwork::AResponse()
{
    _header._responseType = User;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setPassword(password))
        throw BabelErrors::UserResponse("login or password too long");
}

bool BabelNetwork::UserResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    std::strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool BabelNetwork::UserResponse::setPassword(const std::string &password) noexcept
{
    if (password.size() > MaxDataSize::Password)
        return false;
    std::strcat(_data.password, password.c_str());
    _dataInfos._passwordSize = password.size();
    return true;
}

bool BabelNetwork::UserResponse::encode() noexcept
{
    std::memcpy(_data_byte, &_header, HeaderSize);
    std::memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    std::memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    std::memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool BabelNetwork::UserResponse::decode_header() noexcept
{
    std::memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool BabelNetwork::UserResponse::decode_data_infos() noexcept
{
    std::memcpy(&_dataInfos, getDataByteDataInfos(), DataInfosSize);
    return true;
}

bool BabelNetwork::UserResponse::decode_data() noexcept
{
    std::memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    std::memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

bool BabelNetwork::UserResponse::isOk() noexcept
{
    return _header._code == BabelNetwork::UserResponse::ResponseCode::LoggedIn
        || _header._code == BabelNetwork::UserResponse::ResponseCode::AccountCreated
        || _header._code == BabelNetwork::UserResponse::ResponseCode::AccountDeleted;
}

char *BabelNetwork::UserResponse::getDataByte() noexcept
{
    return _data_byte;
}

char *BabelNetwork::UserResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *BabelNetwork::UserResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

size_t BabelNetwork::UserResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t BabelNetwork::UserResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string BabelNetwork::UserResponse::describe_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string BabelNetwork::UserResponse::describe_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}

std::string BabelNetwork::UserResponse::describe_code() const noexcept
{
    for (const auto &pair : codeString) {
        if (getCode() == pair.first)
            return pair.second;
    }
    return "Unknown User Code";
}
