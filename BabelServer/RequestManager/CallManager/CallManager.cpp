//
// Created by encorpluptit on 9/21/20.
//

#include "CallManager.hpp"

using namespace BabelServer;

const std::vector<CallManager::CallResponseFPtr> &CallManager::getCallResponsePtrTab() const
{
    return CallResponsePtrTab;
}

void CallManager::requestCall(
    const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
    const std::shared_ptr<BabelNetwork::CallResponse> &response,
    const BabelNetwork::ClientList &clientList,
    Database &database
) const
{
    // TODO: add check if caller call himself
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(BabelNetwork::CallResponse::CallIncoming(response->getSender(), response->getReceiver(), getCallId()));
//            target->sendResponse(BabelNetwork::CallResponse::CallIncoming(response->getSender(), response->getReceiver(), getCallId()));
            return;
        }
    }
}
