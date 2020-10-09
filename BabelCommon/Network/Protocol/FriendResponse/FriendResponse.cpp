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

FriendResponse::FriendResponse(const std::string &login, const std::string &friendLogin)
    : AResponse()
{
    _header._responseType = Friend;
    _header._dataInfosSize = DataInfosSize;

    if (!setLogin(login) || !setFriendLogin(friendLogin))
        throw BabelErrors::FriendResponse("login or friendLogin too long");
}

bool FriendResponse::setLogin(const std::string &login) noexcept
{
    if (login.size() > MaxDataSize::Login)
        return false;
    std::strcat(_data.login, login.c_str());
    _dataInfos._loginSize = login.size();
    return true;
}

bool FriendResponse::setFriendLogin(const std::string &friendLogin) noexcept
{
    if (friendLogin.size() > MaxDataSize::FriendLogin)
        return false;
    std::strcat(_data.FriendLogin, friendLogin.c_str());
    _dataInfos._friendLoginSize = friendLogin.size();
    return true;
}

bool FriendResponse::encode() noexcept
{
    std::memcpy(_data_byte, &_header, HeaderSize);
    std::memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    std::memcpy(getDataByteBody(), _data.login, _dataInfos._loginSize);
    std::memcpy(getDataByteBody() + _dataInfos._loginSize, _data.FriendLogin, _dataInfos._friendLoginSize);
    return true;
}

bool FriendResponse::decode_header() noexcept
{
    std::memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool FriendResponse::decode_data_infos() noexcept
{
    std::memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool FriendResponse::decode_data() noexcept
{
    std::memcpy(_data.login, getDataByteBody(), _dataInfos._loginSize);
    std::memcpy(_data.FriendLogin, getDataByteBody() + _dataInfos._loginSize, _dataInfos._friendLoginSize);
    return true;
}

bool BabelNetwork::FriendResponse::isOk() noexcept
{
    return _header._code == FriendResponse::ResponseCode::AcceptFriendRequest;
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
    return _dataInfos._loginSize + _dataInfos._friendLoginSize;
}

std::string FriendResponse::describe_data_infos() const noexcept
{
    return BabelUtils::format(
        "Login Size: %zu | FriendLogin Size: %zu",
        _dataInfos._loginSize, _dataInfos._friendLoginSize
    );
}

std::string FriendResponse::describe_data() const noexcept
{
    return BabelUtils::format(
        "Login: %s | FriendLogin: %s",
        _data.login, _data.FriendLogin
    );
}

std::string FriendResponse::describe_code() const noexcept
{
    for (const auto &pair : codeString) {
        if (getCode() == pair.first)
            return pair.second;
    }
    return "Unknown Friend Code";
}
