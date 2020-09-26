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

CallResponse::CallResponse(
    const std::string &sender,
    const std::string &receiver,
    const std::string &address,
    const std::string &port
) : CallResponse(sender, receiver)
{
    if (!setIp(address) || !setPort(port))
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

bool CallResponse::setIp(const std::string &ip) noexcept
{
    if (ip.size() > MaxDataSize::Ip)
        return false;
    strcat(_data.ip, ip.c_str());
    _dataInfos._ipSize = ip.size();
    return true;
}

bool CallResponse::setPort(const std::string &port) noexcept
{
    if (port.size() > MaxDataSize::Port)
        return false;
    strcat(_data.port, port.c_str());
    _dataInfos._portSize = port.size();
    return true;
}


bool CallResponse::encode() noexcept
{
    char *const sender = getDataByteBody();
    char *const receiver = sender + _dataInfos._senderSize;
    char *const timestamp = receiver + _dataInfos._receiverSize;
    char *const call_id = timestamp + _dataInfos._timestampSize;
    char *const ip = call_id + _dataInfos._callIdSize;
    char *const port = ip + _dataInfos._ipSize;

    memcpy(_data_byte, &_header, HeaderSize);
    memcpy(getDataByteDataInfos(), &_dataInfos, DataInfosSize);
    memcpy(sender, _data.sender, _dataInfos._senderSize);
    memcpy(receiver, _data.receiver, _dataInfos._receiverSize);
    memcpy(timestamp, &_data.timestamp, _dataInfos._timestampSize);
    memcpy(call_id, &_data.callId, _dataInfos._callIdSize);
    memcpy(ip, _data.ip, _dataInfos._ipSize);
    memcpy(port, _data.port, _dataInfos._portSize);
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
    char *const sender = getDataByteBody();
    char *const receiver = sender + _dataInfos._senderSize;
    char *const timestamp = receiver + _dataInfos._receiverSize;
    char *const call_id = timestamp + _dataInfos._timestampSize;
    char *const ip = call_id + _dataInfos._callIdSize;
    char *const port = ip + _dataInfos._ipSize;

    memcpy(_data.sender, sender, _dataInfos._senderSize);
    memcpy(_data.receiver, receiver, _dataInfos._receiverSize);
    memcpy(&_data.timestamp, timestamp, _dataInfos._timestampSize);
    memcpy(&_data.callId, call_id, _dataInfos._callIdSize);
    memcpy(_data.ip, ip, _dataInfos._ipSize);
    memcpy(_data.port, port, _dataInfos._portSize);

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
        + _dataInfos._timestampSize + _dataInfos._callIdSize
        + _dataInfos._ipSize + _dataInfos._portSize;
}

std::string CallResponse::describe_data_infos() const noexcept
{
    return BabelUtils::format(
        "Sender Size: %zu | Receiver Size: %zu | Timestamp Size : %zu | CallId Size : %zu",
        _dataInfos._senderSize, _dataInfos._receiverSize, _dataInfos._timestampSize, _dataInfos._callIdSize,
        _dataInfos._ipSize, _dataInfos._portSize
    );
}

std::string CallResponse::describe_data() const noexcept
{
    return BabelUtils::format(
        "Sender: %s | Receiver: %s | Timestamp : %ld | CallId: %u | Ip: %s | Port: %s",
        _data.sender, _data.receiver, _data.timestamp, _data.callId, _data.ip, _data.port
    );
}

std::string CallResponse::describe_code() const noexcept
{
    for (const auto &pair : codeString) {
        if (getCode() == pair.first)
            return pair.second;
    }
    return "Unknown Call Code";
}
