/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include "StringFormat.tpp"
#include "AResponse.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

AResponse::AResponse(const ResponseHeader &headerResponse)
    : _header(headerResponse)
{
}

AResponse::AResponse(const AResponse &other) : AResponse(other._header)
{
}

std::shared_ptr<AResponse> AResponse::getResponse(const char *headerBuffer)
{
//    ResponseHeader response(headerBuffer);

    ResponseHeader response{};
    memcpy(&response, headerBuffer, HeaderSize);
//    //Todo Switch case for returning good ptr
    switch (response._responseType) {
        case Connection:
            return std::shared_ptr<AResponse>(new ConnectionResponse(response));
        default:
            return nullptr;
    }
}

std::string AResponse::serialize() const noexcept
{
    std::string serialised = BabelUtils::format(
        R"({"Code": "%d", "Data Infos Size": "%zu", "Desc": "%s"})"
        "\n\t" R"({"Data Infos": ")" + serialize_data_infos() + "\"}" +
            "\n\t" R"({"Data": ")" + serialize_data() + "\"}",
        getCode(), getDataInfosSize(), getDescription().c_str()
    );
    return serialised;
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.serialize();
    return os;
}

uint16_t AResponse::getCode() const noexcept
{
    return _header._code;
}

[[nodiscard]] size_t AResponse::getDataInfosSize() const noexcept
{
    return _header._dataInfosSize;
}

AResponse::ResponseType AResponse::getResponseType() const
{
    return _header._responseType;
}
