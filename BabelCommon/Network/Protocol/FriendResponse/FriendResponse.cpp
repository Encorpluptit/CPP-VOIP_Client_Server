/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [FriendResponse.cpp]: Source file for FriendResponse feature.
*/

#include "FriendResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

FriendResponse::FriendResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse) {}

FriendResponse::FriendResponse(const std::string &login, const std::string &password)
    : AResponse()
{
    _header._responseType = Friend;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setPassword(password))
        throw BabelErrors::FriendResponse("login or password too long");
}

bool FriendResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool FriendResponse::setPassword(const std::string &password) noexcept
{
    if (password.size() > MaxDataSize::Password)
        return false;
    strcat(_data.password, password.c_str());
    _dataInfos._passwordSize = password.size();
    return true;
}

bool FriendResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool FriendResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool FriendResponse::decode_data_infos() noexcept
{
    memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool FriendResponse::decode_data() noexcept
{
    memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

bool BabelNetwork::FriendResponse::isOk() noexcept
{
    return _header._code == FriendResponse::ResponseCode::LoginOk
        || _header._code == FriendResponse::ResponseCode::AccountCreated
        || _header._code == FriendResponse::ResponseCode::AccountDeleted;
}

std::shared_ptr<AResponse> FriendResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<FriendResponse>(*this);
}

char *FriendResponse::getDataByte() noexcept
{
    return _data_byte;
}

char *FriendResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *FriendResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

size_t FriendResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t FriendResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string FriendResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string FriendResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}
