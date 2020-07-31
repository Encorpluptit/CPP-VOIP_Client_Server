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
AResponse::AResponse(const ResponseHeader &headerResponse)
{
    _header.returnCode = headerResponse.returnCode;
    _header.dataLength = headerResponse.dataLength;
    _header.responseType = headerResponse.responseType;
}

std::shared_ptr<AResponse> AResponse::getResponse(const ResponseHeader &response)
{
//    //Todo Switch case for returning good ptr
    switch (response.responseType) {
        case Connection:
            return std::shared_ptr<AResponse>(new ConnectionResponse(response));
        default:
            return nullptr;
    }
}
//
//std::shared_ptr<AResponse> AResponse::getResponse()
//{
//    switch (getResponseType()) {
//        case Connection:
////            return std::make_shared<ConnectionResponse>(static_cast<ConnectionResponse>(this));
//            return std::shared_ptr<ConnectionResponse>(dynamic_cast<ConnectionResponse *>(this));
////            return std::shared_ptr<AResponse>(new ConnectionResponse(static_cast<ConnectionResponse>(response)));
//        default:
//            return nullptr;
//    }
//}

bool AResponse::encode_header() noexcept
{
    memcpy(_headerData, &_header, ResponseHeaderSize);
    return true;
}

bool AResponse::decode_header() noexcept
{
    memcpy(&_header, _headerData, ResponseHeaderSize);
    return true;
}

std::string AResponse::serialize() const
{
    std::string response = \
    R"({"Code": )" + std::to_string(getCode())      \
 + R"(, "Desc": ")" + getDescription() + "\""        \
 + R"(, "Data": ")"                   \
 + "\"}";
    return response;
//    std::string response = \
//    R"({"Code": )" + std::to_string(getCode())      \
// + R"(, "Desc": ")" + getDescription() + "\""        \
// + R"(, "Data": ")" + getBodyData()                  \
// + "\"}";
//    return response;
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.serialize();
    return os;
}

uint16_t AResponse::getCode() const noexcept
{
    return _header.returnCode;
}

[[nodiscard]] uint32_t AResponse::getHeaderDataLength() const noexcept
{
    return _header.dataLength;
}

char *AResponse::getHeaderData()
{
    return _headerData;
}
//
//constexpr size_t AResponse::getHeaderSize()
//{
//    return ResponseHeaderSize;
//}

const AResponse::ResponseType &AResponse::getResponseType() const
{
    return _header.responseType;
}
//
//std::shared_ptr<AResponse> AResponse::getResponse(const AResponse &response)
//{
//    return std::shared_ptr<AResponse>();
//}
