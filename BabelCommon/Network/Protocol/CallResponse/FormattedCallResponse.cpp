/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 8/21/20).
** File description:
** [FormattedCallResponse.cpp]: Source file for FormattedCallResponse feature.
*/

#include <iostream>
#include "CallResponse.hpp"

using namespace BabelNetwork;

std::shared_ptr<AResponse> CallResponse::NewCallStarted(
    const std::string &sender,
    const std::string &receiver
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::CallStarted);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::NewCallStarted(
    const std::string &sender,
    const std::string &receiver,
    const std::string &ip,
    const std::string &port
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver, ip, port);

    resp->setCode(CallResponse::ResponseCode::CallStarted);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::CallRequest(
    const std::string &sender,
    const std::string &receiver,
    const std::string &ip,
    const std::string &port
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver, ip, port);

    resp->setCode(CallResponse::ResponseCode::RequestCall);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::LeftCall(
    const std::string &sender,
    const std::string &receiver,
    const uint16_t call_id
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::CallLeft);
    if (!resp->setCallId(call_id) || !resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::EndCallRequest(const std::string &sender, const std::string &receiver)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::RequestEndCall);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::CallIncoming(
    const std::shared_ptr<CallResponse> &resp,
    const uint16_t call_id
)
{
    resp->setCode(CallResponse::ResponseCode::IncomingCall);
    if (!resp->setCallId(call_id) || !resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::AcceptCall(
    const std::string &sender,
    const std::string &receiver,
    const std::string &ip,
    const std::string &port
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::CallAccepted);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::RefusedCall(const std::string &sender, const std::string &receiver)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::CallRefused);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::DisconnectedUser(
    const std::string &sender,
    const std::string &receiver
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::UserDisconnected);
    if (!resp->setTimestamp())
        return nullptr;
    return resp;
}

std::shared_ptr<AResponse> CallResponse::UnknownErrorOccured(
    const std::shared_ptr<BabelNetwork::CallResponse> &response
)
{
    response->setCode(CallResponse::ResponseCode::UnknownError);
    return response;
}
