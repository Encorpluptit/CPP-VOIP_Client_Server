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

MessageResponse::MessageResponse(const std::string &sender, const std::string &receiver, const std::string &messageData)
    : AResponse()
{
    _header._responseType = Message;
    _header._dataInfosSize = DataInfosSize;

    if (!setSender(sender) || !setReceiver(receiver) || !setMessageData(messageData))
        throw BabelErrors::MessageResponse("sender or receiver or message too long");
}

bool MessageResponse::setSender(const std::string &sender) noexcept
{
    if (sender.size() > MaxDataSize::Sender)
        return false;
    strcat(_data.sender, sender.c_str());
    _dataInfos._senderSize = sender.size();
    return true;
}

bool MessageResponse::setReceiver(const std::string &receiver) noexcept
{
    if (receiver.size() > MaxDataSize::Receiver)
        return false;
    strcat(_data.receiver, receiver.c_str());
    _dataInfos._receiverSize = receiver.size();
    return true;
}

bool MessageResponse::setMessageData(const std::string &messageData) noexcept
{
    if (messageData.size() > MaxDataSize::MessageData)
        return false;
    strcat(_data.messageData, messageData.c_str());
    _dataInfos._messageDataSize = messageData.size();
    return true;
}

bool MessageResponse::setTimestamp() noexcept
{
    std::time_t timer;
    if (std::time(&timer) == ((std::time_t) -1))
        return false;
    _data.timestamp = timer;
    _dataInfos._timestampSize = sizeof(_data.timestamp);
    return true;
}

bool MessageResponse::encode() noexcept
{
    std::memcpy(_data_byte, &_header, HeaderSize);
    std::memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    std::memcpy(getDataByteBody(), _data.sender, _dataInfos._senderSize);
    std::memcpy(getDataByteBody() + _dataInfos._senderSize, _data.receiver, _dataInfos._receiverSize);
    std::memcpy(getDataByteBody() + _dataInfos._senderSize + _dataInfos._receiverSize, &_data.timestamp,
        _dataInfos._timestampSize);
    return true;
}

bool MessageResponse::decode_header() noexcept
{
    std::memcpy(&_header, _data_byte, HeaderSize);
    return true;
}

bool MessageResponse::decode_data_infos() noexcept
{
    std::memcpy(&_dataInfos, _data_byte + HeaderSize, DataInfosSize);
    return true;
}

bool MessageResponse::decode_data() noexcept
{
    std::memcpy(_data.sender, getDataByteBody(), _dataInfos._senderSize);
    std::memcpy(_data.receiver, getDataByteBody() + _dataInfos._senderSize, _dataInfos._receiverSize);
    std::memcpy(&_data.timestamp, getDataByteBody() + _dataInfos._senderSize + _dataInfos._receiverSize,
        _dataInfos._timestampSize);
    return true;
}

bool BabelNetwork::MessageResponse::isOk() noexcept
{
    return _header._code;
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
    return _dataInfos._senderSize + _dataInfos._receiverSize;
}

std::string MessageResponse::describe_data_infos() const noexcept
{
    return BabelUtils::format(
        "Sender Size: %zu | Receiver Size: %zu",
        _dataInfos._senderSize, _dataInfos._receiverSize
    );
}

std::string MessageResponse::describe_data() const noexcept
{
    return BabelUtils::format(
        "Sender: %s | Receiver: %s",
        _data.sender, _data.receiver
    );
}

std::string MessageResponse::describe_code() const noexcept
{
    for (const auto &pair : codeString) {
        if (getCode() == pair.first)
            return pair.second;
    }
    return "Unknown Call Code";
}
