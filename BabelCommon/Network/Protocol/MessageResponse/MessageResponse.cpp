/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [MessageResponse.cpp]: Source file for MessageResponse feature.
*/

#include "MessageResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

MessageResponse::MessageResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse) {}

MessageResponse::MessageResponse(const std::string &login, const std::string &password)
    : AResponse()
{
    _header._responseType = Message;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setPassword(password))
        throw BabelErrors::MessageResponse("login or password too long");
}

bool MessageResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool MessageResponse::setPassword(const std::string &password) noexcept
{
    if (password.size() > MaxDataSize::Password)
        return false;
    strcat(_data.password, password.c_str());
    _dataInfos._passwordSize = password.size();
    return true;
}

bool MessageResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool MessageResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool MessageResponse::decode_data_infos() noexcept
{
    memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool MessageResponse::decode_data() noexcept
{
    memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

bool BabelNetwork::MessageResponse::isOk() noexcept
{
    return _header._code == MessageResponse::ResponseCode::LoginOk
        || _header._code == MessageResponse::ResponseCode::AccountCreated
        || _header._code == MessageResponse::ResponseCode::AccountDeleted;
}

std::shared_ptr<AResponse> MessageResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<MessageResponse>(*this);
}

char *MessageResponse::getDataByte() noexcept
{
    return _data_byte;
}

char *MessageResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *MessageResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

size_t MessageResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t MessageResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string MessageResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string MessageResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}
