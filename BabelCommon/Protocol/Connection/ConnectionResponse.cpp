/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Source file for ConnectionResponse feature.
*/

#include "ConnectionResponse.hpp"

BabelNetwork::ConnectionResponse::ConnectionResponse()
{
    _description = "Connection between server and client";
}

bool BabelNetwork::ConnectionResponse::isOk()
{
    return _code == IResponse::ResponseCode::ConnectionOk;
}
