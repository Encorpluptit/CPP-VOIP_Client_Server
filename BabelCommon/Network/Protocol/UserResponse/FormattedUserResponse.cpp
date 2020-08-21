/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormatedUserResponse.cpp]: Source file for FormatedUserResponse feature.
*/

#include "UserResponse.hpp"

using namespace BabelNetwork;

std::shared_ptr<AResponse> UserResponse::NewLoginRequest(const std::string &login, const std::string &password)
{
    auto resp = std::make_shared<UserResponse>(login, password);

    resp->setCode(UserResponse::ResponseCode::RequestLogin);
    return resp;
}
