/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [CallResponse.cpp]: Source file for CallResponse feature.
*/

#include "CallResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

CallResponse::CallResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse) {}

CallResponse::CallResponse(const std::string &login, const std::string &password)
    : AResponse()
{
    _header._responseType = Call;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setPassword(password))
        throw BabelErrors::CallResponse("login or password too long");
}

bool CallResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool CallResponse::setPassword(const std::string &password) noexcept
{
    if (password.size() > MaxDataSize::Password)
        return false;
    strcat(_data.password, password.c_str());
    _dataInfos._passwordSize = password.size();
    return true;
}

bool CallResponse::encode() noexcept
{
    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    memcpy(getDataByteBody() + _dataInfos._loginSize, _data.password, _dataInfos._passwordSize);
    return true;
}

bool CallResponse::decode_header() noexcept
{
    memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool CallResponse::decode_data_infos() noexcept
{
    memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool CallResponse::decode_data() noexcept
{
    memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    memcpy(_data.password, getDataByteBody() + _dataInfos._loginSize, _dataInfos._passwordSize);
    return true;
}

bool BabelNetwork::CallResponse::isOk() noexcept
{
    return _header._code == CallResponse::ResponseCode::LoginOk
        || _header._code == CallResponse::ResponseCode::AccountCreated
        || _header._code == CallResponse::ResponseCode::AccountDeleted;
}

std::shared_ptr<AResponse> CallResponse::get_shared_from_this() const noexcept
{
    return std::make_shared<CallResponse>(*this);
}

char *CallResponse::getDataByte() noexcept
{
    return _data_byte;
}

char *CallResponse::getDataByteDataInfos() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize);
}

char *CallResponse::getDataByteBody() const noexcept
{
    return const_cast<char *>(_data_byte + HeaderSize + DataInfosSize);
}

size_t CallResponse::getResponseSize() const noexcept
{
    return HeaderSize + DataInfosSize + getDataSize();
}

size_t CallResponse::getDataSize() const noexcept
{
    return _dataInfos._loginSize + _dataInfos._passwordSize;
}

std::string CallResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | Password Size: %zu",
        _dataInfos._loginSize, _dataInfos._passwordSize
    );
}

std::string CallResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | Password: %s",
        _data.login, _data.password
    );
}
