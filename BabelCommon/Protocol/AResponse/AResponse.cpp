/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include "AResponse.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

AResponse::AResponse(const ResponseHeader &headerResponse)
{
    _header = Response(headerResponse);
}

AResponse::AResponse(const AResponse &other) : AResponse(other._header)
{
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
    std::string response =                                  \
    R"({"Code": )" + std::to_string(getCode())          \
 + R"(", Body Size": )" + std::to_string(getBodySize()) \
 + R"(, "Desc": ")" + getDescription() + "\"}\n"            \
 + R"({"Data": ")" + serialize_data()                      \
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
    return _header.code;
}

[[nodiscard]] uint32_t AResponse::getBodySize() const noexcept
{
    return _header.bodySize;
}

AResponse::ResponseType AResponse::getResponseType() const
{
    return _header.responseType;
}
