/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include "StringFormat.tpp"
#include "AResponse.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

using namespace BabelNetwork;

AResponse::AResponse(const ResponseHeader &headerResponse)
    : _header(headerResponse)
{}

AResponse::AResponse(const AResponse &other) : AResponse(other._header)
{}

std::shared_ptr<AResponse> AResponse::getResponse(const char *headerBuffer)
{
    ResponseHeader response{};
    memcpy(&response, headerBuffer, HeaderSize);

    switch (response._responseType) {
        case User:
            return std::shared_ptr<AResponse>(new UserResponse(response));
        case Call:
            return std::shared_ptr<AResponse>(new CallResponse(response));
        case Friend:
            return std::shared_ptr<AResponse>(new FriendResponse(response));
        case Message:
            return std::shared_ptr<AResponse>(new MessageResponse(response));
        default:
            return nullptr;
    }
}

std::string AResponse::describe() const noexcept
{
    std::string serialised = BabelUtils::format(
        "%s\n"
        R"({"Code": "%d", "Data Infos Size": "%zu", "Desc": "%s"})"
        "\n\t" R"({"Data Infos": ")" + describe_data_infos() + "\"}" +
            "\n\t" R"({"Data": ")" + describe_data() + "\"}",
        describe_code().c_str(), getCode(), getDataInfosSize(), getDescription().c_str()
    );
    return serialised;
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.describe();
    return os;
}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const std::shared_ptr<AResponse> &response)
{
    os << response->describe();
    return os;
}

uint16_t AResponse::getCode() const noexcept
{
    return _header._code;
}

void AResponse::setCode(uint16_t code) noexcept
{
    _header._code = code;
}

[[nodiscard]] size_t AResponse::getDataInfosSize() const noexcept
{
    return _header._dataInfosSize;
}

AResponse::ResponseType AResponse::getResponseType() const
{
    return _header._responseType;
}

AResponse::ResponseHeader AResponse::getResponseHeader() const
{
    return (_header);
}