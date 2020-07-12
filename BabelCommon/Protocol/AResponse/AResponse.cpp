/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.cpp]: Source file for AResponse feature.
*/

#include "AResponse.hpp"
#include "ConnectionResponse.hpp"

using namespace BabelNetwork;

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.serialize();
    return os;
}

int BabelNetwork::AResponse::getCode() const
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

std::unique_ptr<IResponse> AResponse::getResponse(const std::string &input)
{

    return std::unique_ptr<IResponse>(new ConnectionResponse());
}

std::string AResponse::serialize() const
{
    std::string response = R"({"Code": )" + std::to_string(getCode()) + R"(, "Desc": ")" + getDescription() + "\"";
    if (getData().empty())
        response += R"(, "Data": ""})";
    else
        response += R"(, "Data": ")" + getData() + "\"}";
    return response;
}
