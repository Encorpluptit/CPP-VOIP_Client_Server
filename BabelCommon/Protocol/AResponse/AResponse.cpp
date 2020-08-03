/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

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

std::string AResponse::serialize() const
{
    std::string response =                              \
    R"({"Code": )" + std::to_string(getCode())      \
 + R"(, "Desc": ")" + getDescription() + "\""           \
 + R"(, "Data": ")" + serialize_data()                  \
 + "\"}";
    return response;
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

[[nodiscard]] uint32_t AResponse::getBodySize() const noexcept
{
    return _header.dataLength;
}

AResponse::ResponseType AResponse::getResponseType() const
{
    return _header.responseType;
}

char *AResponse::getHeaderData()
{
    return reinterpret_cast<char *>(&_header);
}
