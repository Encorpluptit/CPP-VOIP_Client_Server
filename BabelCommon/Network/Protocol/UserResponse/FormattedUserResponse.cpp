/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormatedUserResponse.cpp]: Source file for FormatedUserResponse feature.
*/

#include "UserResponse.hpp"

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::UserResponse::NewLoginRequest(const std::string &login, const std::string &password)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, password);

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::RequestLogin);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::LogoutRequest(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::RequestLogout);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::UserResponse::AccountCreationRequest(const std::string &login, const std::string &password)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, password);

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::RequestAccountCreation);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::AccountDeletionRequest(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::RequestAccountDeletion);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::LoggedInOk(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::LoggedIn);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::LoggedOutOk(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::LoggedOut);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::AccountCreatedOk(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::AccountCreated);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::AccountDeletedOk(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::AccountDeleted);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::UnknownError(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::UnknownUserError);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::BadLogin(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::WrongLogin);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::BadPassword(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::WrongPassword);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::LoginAlreadyUsed(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::LoginAlreadyTaken);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::AlreadyLog(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::AlreadyLoggedIn);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::RequestedDeletedAccount(const std::string &login)
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>(login, "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::RequestedAccountDeleted);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse> BabelNetwork::UserResponse::ClientNotLogged()
{
    auto resp = std::make_shared<BabelNetwork::UserResponse>("", "");

    resp->setCode(BabelNetwork::UserResponse::ResponseCode::ClientLoggedOut);
    return resp;
}
