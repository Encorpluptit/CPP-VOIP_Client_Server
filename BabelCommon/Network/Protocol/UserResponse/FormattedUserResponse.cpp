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

std::shared_ptr<AResponse> UserResponse::LogoutRequest(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::RequestLogout);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::AccountCreationRequest(const std::string &login, const std::string &password)
{
    auto resp = std::make_shared<UserResponse>(login, password);

    resp->setCode(UserResponse::ResponseCode::RequestAccountCreation);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::AccountDeletionRequest(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::RequestAccountDeletion);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::LoggingInOk(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::LoggedIn);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::LoggedOutOk(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::LoggedOut);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::AccountCreatedOk(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::AccountCreated);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::AccountDeletedOk(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::AccountDeleted);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::UnknowUser(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::UnknownUserError);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::BadLogin(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::WrongLogin);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::BadPassword(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::WrongPassword);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::LoginUse(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::LoginAlreadyTaken);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::AlreadyLog(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::AlreadyLoggedIn);
    return resp;
}

std::shared_ptr<AResponse> UserResponse::RequestedDeletedAccount(const std::string &login)
{
    auto resp = std::make_shared<UserResponse>(login, "");

    resp->setCode(UserResponse::ResponseCode::RequestedAccountDeleted);
    return resp;
}