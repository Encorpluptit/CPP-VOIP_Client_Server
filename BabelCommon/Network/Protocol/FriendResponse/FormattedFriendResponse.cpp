/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormatedFriendResponse.cpp]: Source file for FormatedFriendResponse feature.
*/

#include "FriendResponse.hpp"

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::RequestFriend(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(BabelNetwork::FriendResponse::ResponseCode::RequestAddFriend);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::AddFriend(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(BabelNetwork::FriendResponse::ResponseCode::FriendAdded);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::NewFriendRequest(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(BabelNetwork::FriendResponse::ResponseCode::NewFriendshipRequested);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::NewFriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(BabelNetwork::FriendResponse::ResponseCode::NewFriendshipRequested);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::FriendRequestAccepted(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::AcceptFriendRequest);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::FriendRequestDeclined(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(BabelNetwork::FriendResponse::ResponseCode::DeclineFriendRequest);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::UserNotExist(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(FriendResponse::ResponseCode::UnknownUser);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::DeleteFriendOK(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::FriendDeleted);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::DeleteFriendOK(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(FriendResponse::ResponseCode::FriendDeleted);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::DeleteFriendRequest(const std::string &login, const std::string &friendLogin)
{
    auto resp = std::make_shared<BabelNetwork::FriendResponse>(login, friendLogin);

    resp->setCode(FriendResponse::ResponseCode::RequestDeleteFriend);
    return resp;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::FriendshipExist(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(FriendResponse::ResponseCode::FriendshipAlreadyExist);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::UnknownFriendship(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(FriendResponse::ResponseCode::FriendshipUnknown);
    return response;
}

std::shared_ptr<BabelNetwork::AResponse>
BabelNetwork::FriendResponse::UnknownErrorOccured(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    response->setCode(FriendResponse::ResponseCode::UnknownErrorOccur);
    return response;
}

