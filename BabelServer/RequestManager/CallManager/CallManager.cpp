//
// Created by encorpluptit on 9/21/20.
//

#include "CallManager.hpp"

using namespace BabelServer;
using namespace BabelNetwork;

const std::vector<CallManager::CallResponseFPtr> &CallManager::getCallResponsePtrTab() const
{
    return CallResponsePtrTab;
}

void CallManager::requestCall(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::CallResponse> &response,
    const BabelNetwork::ClientList &clientList
) const
{
    // TODO: add check if caller call himself
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(CallResponse::CallIncoming(response, getCallId()));
            // TODO: Adding Increment (pb with const)
//            incrementCallId();
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));
}

void CallManager::refuseCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &response,
    const ClientList &clientList
) const
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(response);
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));
}

void CallManager::acceptCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &response,
    const ClientList &clientList
) const
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(response);
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));
}
