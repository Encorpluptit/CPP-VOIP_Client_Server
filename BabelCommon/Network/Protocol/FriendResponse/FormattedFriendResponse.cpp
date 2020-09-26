/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormatedFriendResponse.cpp]: Source file for FormatedFriendResponse feature.
*/

#include "FriendResponse.hpp"

using namespace BabelNetwork;

std::shared_ptr<AResponse> FriendResponse::RequestFriend(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::RequestAddFriend);
    return resp;
}

std::shared_ptr<AResponse> FriendResponse::FriendRequestOk(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::AddFriend);
    return resp;
}

std::shared_ptr<AResponse> FriendResponse::NewFriendRequest(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::FriendRequest);
    return resp;
}

std::shared_ptr<AResponse> FriendResponse::FriendRequestAccepted(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::AcceptFriendRequest);
    return resp;
}

std::shared_ptr<AResponse> FriendResponse::FriendRequestDeclined(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::DeclineFriendRequest);
    return resp;
}

std::shared_ptr<AResponse> FriendResponse::UserNotExist(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::UnknownUser);
    return resp;
}