/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include "AResponse.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

AResponse::AResponse(const ResponseHeader *response, const char *data)
    : _code(response->returnCode),
    _data(data ? data : std::string().c_str())
{}

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.serialize();
    return os;
}

uint16_t BabelNetwork::AResponse::getCode() const
{
    return _code;
}

const std::string &BabelNetwork::AResponse::getDescription() const
{
    return _description;
}

const std::string &AResponse::getData() const
{
    return _data;
}

void AResponse::setData(const std::string &data)
{
    _data = data;
}

std::unique_ptr<IResponse> AResponse::getResponse(ResponseHeader *response, const char *data)
{

    return std::unique_ptr<IResponse>(new ConnectionResponse(response, data));
}

std::string AResponse::serialize() const
{
    std::string response = \
    R"({"Code": )" + std::to_string(getCode())      \
    + R"(, "Desc": ")" + getDescription() + "\""        \
    + R"(, "Data": ")" + getData()                      \
    + "\"}";
    return response;
}
