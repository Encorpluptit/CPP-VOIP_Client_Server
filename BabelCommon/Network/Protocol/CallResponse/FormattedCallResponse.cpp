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
    const std::string &receiver,
    const std::string &ip,
    const std::string &port,
    const uint16_t call_id
)
{
    auto response = std::make_shared<CallResponse>(
        sender, receiver, ip, port
    );

    response->setCode(CallResponse::ResponseCode::CallStarted);
    if (!response->setCallId(call_id) || !response->setTimestamp())
        return nullptr;
    return response;
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
    return resp;
}

std::shared_ptr<AResponse> CallResponse::LeftCall(
    const std::string &sender,
    const std::string &receiver
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::CallLeft);
    return resp;
}

std::shared_ptr<AResponse> CallResponse::EndCallRequest(
    const std::shared_ptr<BabelNetwork::CallResponse> &resp
)
{
    auto response = std::make_shared<CallResponse>(
        resp->getReceiver(), resp->getSender(), resp->getIp(), resp->getPort()
    );

    response->setCode(CallResponse::ResponseCode::RequestEndCall);
    return response;
}

std::shared_ptr<AResponse> CallResponse::CallIncoming(
    const std::shared_ptr<CallResponse> &resp,
    const uint16_t call_id
)
{
    auto response = std::make_shared<CallResponse>(
        resp->getSender(), resp->getReceiver(), resp->getIp(), resp->getPort()
    );

    response->setCode(CallResponse::ResponseCode::IncomingCall);
    if (!response->setCallId(call_id))
        return nullptr;
    return response;
}

std::shared_ptr<AResponse> CallResponse::AcceptCall(
    const std::shared_ptr<BabelNetwork::CallResponse> &resp,
    const uint16_t port
)
{
    auto response = std::make_shared<CallResponse>(
        resp->getReceiver(), resp->getSender(), resp->getIp(), std::to_string(port)
    );

    response->setCode(CallResponse::ResponseCode::CallAccepted);
    if (!response->setCallId(resp->getCallId()))
        return nullptr;
    return response;
}

std::shared_ptr<AResponse> CallResponse::RefusedCall(
    const std::shared_ptr<BabelNetwork::CallResponse> &resp
)
{
    auto response = std::make_shared<CallResponse>(
        resp->getReceiver(), resp->getSender(), resp->getIp(), resp->getPort()
    );

    response->setCode(CallResponse::ResponseCode::CallRefused);
    if (!response->setCallId(resp->getCallId()))
        return nullptr;
    return response;
}

std::shared_ptr<AResponse> CallResponse::DisconnectedUser(
    const std::string &sender,
    const std::string &receiver
)
{
    auto resp = std::make_shared<CallResponse>(sender, receiver);

    resp->setCode(CallResponse::ResponseCode::UserDisconnected);
    return resp;
}

std::shared_ptr<AResponse> CallResponse::UnknownErrorOccured(
    const std::shared_ptr<BabelNetwork::CallResponse> &resp
)
{
    auto response = std::make_shared<CallResponse>(
        resp->getReceiver(), resp->getSender(), resp->getIp(), resp->getPort()
    );

    response->setCode(CallResponse::ResponseCode::UnknownError);
    return response;
}
