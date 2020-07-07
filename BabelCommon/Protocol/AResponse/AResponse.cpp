/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20.
** File description:
** [AResponse.cpp]: Header file for AResponse feature.
*/

#include "AResponse.hpp"

using namespace BabelNetwork;

std::ostream &BabelNetwork::operator<<(std::ostream &os, const BabelNetwork::AResponse &response)
{
    os << response.getCode() << ":\t" << response.getDescription();
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
