/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [ConnectionResponse.cpp]: Header file for ConnectionResponse feature.
*/

#include "ConnectionResponse.hpp"

bool BabelNetwork::ConnectionResponse::isOk()
{
    return _code == IResponse::ResponseCode::ConnectionOk;
}
