/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include <cstring>
#include "AResponse.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

// TODO: real constructor for ResponseHeader Structure
AResponse::AResponse(const AResponse::ResponseHeader *response)
{
    _header.returnCode = response->returnCode;
    _header.dataLength = response->dataLength;
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.serialize();
    return os;
}

uint16_t AResponse::getCode() const
{
    return _header.returnCode;
}

[[nodiscard]] uint32_t AResponse::getHeaderDataLength() const
{
    return _header.dataLength;
}
//
//const std::string &BabelNetwork::AResponse::getDescription() const
//{
//    return _description;
//}

std::shared_ptr<IResponse> AResponse::getResponse(ResponseHeader *response, const char *data)
{
    //Todo Switch case for returning good ptr
    if (response->returnCode >= IResponse::ResponseCode::ConnectionOk)
        return std::unique_ptr<IResponse>(new ConnectionResponse(response));
//    switch {
//        case (IResponse::ResponseCode::
//    }
    return std::unique_ptr<IResponse>(new ConnectionResponse(response));
}

std::string AResponse::serialize() const
{
    std::string response = \
    R"({"Code": )" + std::to_string(getCode())      \
 + R"(, "Desc": ")" + getDescription() + "\""        \
 + R"(, "Data": ")" + getBodyData()                  \
 + "\"}";
    return response;
}

bool AResponse::encode_header()
{
    memcpy(_headerData, &_header, ResponseHeaderSize);
    return true;
}

bool AResponse::decode_header()
{
    memcpy(&_header, _headerData, ResponseHeaderSize);
    return false;
}

constexpr size_t AResponse::getResponseHeaderSize()
{
    return ResponseHeaderSize;
}

const char *AResponse::getHeaderData() const
{
    return _headerData;
}
