/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [CallResponse.cpp]: Source file for CallResponse feature.
*/

#include <ctime>
#include "CallResponse.hpp"
#include "StringFormat.tpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

CallResponse::CallResponse(const ResponseHeader &headerResponse)
    : AResponse(headerResponse) {}

CallResponse::CallResponse(const std::string &sender, const std::string &receiver)
    : AResponse()
{
    _header._responseType = Call;
    _header._dataInfosSize = DataInfosSize;

    if (!setSender(sender) || !setReceiver(receiver))
        throw BabelErrors::CallResponse("sender or receiver too long");
}

bool CallResponse::setSender(const std::string &sender) noexcept
{
    if (sender.size() > MaxDataSize::Sender)
        return false;
    strcat(_data.sender, sender.c_str());
    _dataInfos._senderSize = sender.size();
    return true;
}

bool CallResponse::setReceiver(const std::string &receiver) noexcept
{
    if (receiver.size() > MaxDataSize::Receiver)
        return false;
    strcat(_data.receiver, receiver.c_str());
    _dataInfos._receiverSize = receiver.size();
    return true;
}

bool CallResponse::setTimestamp() noexcept
{
    time_t timer;
    if (time(&timer) == ((time_t) -1))
        return false;
    _data.timestamp = timer;
    _dataInfos._timestampSize = sizeof(_data.timestamp);
    return true;
}

bool CallResponse::setCallId(const uint16_t call_id) noexcept
{
    if (!call_id)
        return false;
    _data.callId = call_id;
    _dataInfos._callIdSize = sizeof(_data.callId);
    return true;
}

bool CallResponse::encode() noexcept
{
    char * const sender = getDataByteBody();
    char * const receiver = sender + _dataInfos._senderSize;
    char * const timestamp = receiver + _dataInfos._receiverSize;
    char * const call_id = timestamp + _dataInfos._timestampSize;

    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(sender, _data.sender, _dataInfos._senderSize);
    memcpy(receiver, _data.receiver, _dataInfos._receiverSize);
    memcpy(timestamp, &_data.timestamp, _dataInfos._timestampSize);
    memcpy(call_id, &_data.callId, _dataInfos._callIdSize);
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
    char * const sender = getDataByteBody();
    char * const receiver = sender + _dataInfos._senderSize;
    char * const timestamp = receiver + _dataInfos._receiverSize;
    char * const call_id = timestamp + _dataInfos._timestampSize;

    memcpy(_data.sender, sender, _dataInfos._senderSize);
    memcpy(_data.receiver, receiver, _dataInfos._receiverSize);
    memcpy(&_data.timestamp, timestamp, _dataInfos._timestampSize);
    memcpy(&_data.callId, call_id, _dataInfos._callIdSize);

    return true;
}

bool BabelNetwork::CallResponse::isOk() noexcept
{
    return _header._code != CallResponse::ResponseCode::CallRefused
        && _header._code != CallResponse::ResponseCode::UserDisconnected;
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
    return _dataInfos._senderSize + _dataInfos._receiverSize
    + _dataInfos._timestampSize + _dataInfos._callIdSize;
}

std::string CallResponse::serialize_data_infos() const noexcept
{
    return BabelUtils::format(
        "Sender Size: %zu | Receiver Size: %zu | Timestamp Size : %zu | CallId Size : %zu",
        _dataInfos._senderSize, _dataInfos._receiverSize, _dataInfos._timestampSize, _dataInfos._callIdSize
    );
}

std::string CallResponse::serialize_data() const noexcept
{
    return BabelUtils::format(
        "Sender: %s | Receiver: %s | Timestamp : %ld | CallId: %u",
        _data.sender, _data.receiver,_data.timestamp, _data.callId
    );
}
