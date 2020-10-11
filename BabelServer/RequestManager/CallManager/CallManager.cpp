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
)
{
    if (clientSocket->getUser()->login == response->getReceiver()) {
        clientSocket->sendResponse(CallResponse::UnknownErrorOccured(response));
        return;
    }
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            target->sendResponse(CallResponse::CallIncoming(response, getCallId()));
            _confs.emplace_back(Conference(getCallId(), response->getIp(), response->getPort()));
            incrementCallId();
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));
}

void CallManager::refuseCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &response,
    const ClientList &clientList
)
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == response->getReceiver()) {
            deleteConf(response->getCallId());
            target->sendResponse(response);
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(response->getSender(), response->getReceiver()));
}

void CallManager::acceptCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &resp,
    const ClientList &clientList
)
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == resp->getReceiver()) {
            auto call_id = resp->getCallId();
            for (auto &conf: _confs) {
                if (conf.getCallId() != call_id)
                    continue;
                conf.setReceiver(resp->getIp(), resp->getPort());
                target->sendResponse(CallResponse::NewCallStarted(
                    resp->getReceiver(), resp->getSender(), conf.getReceiverIp(), conf.getReceiverPort(), call_id));
                clientSocket->sendResponse(CallResponse::NewCallStarted(
                    resp->getSender(), resp->getReceiver(), conf.getSenderIp(), conf.getSenderPort(), call_id));
                return;
            }

//            if (updateConf(resp->getCallId(), resp->getIp(), resp->getPort())) {
//                target->sendResponse(CallResponse::NewCallStarted(resp, resp->getReceiver(), resp->getSender()));
//                clientSocket->sendResponse(
//                    CallResponse::NewCallStarted(resp, resp->getSender(), resp->getReceiver()));
//                return;
//            }
            clientSocket->sendResponse(CallResponse::DisconnectedUser(resp->getSender(), resp->getReceiver()));
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(resp->getSender(), resp->getReceiver()));
}

void CallManager::endCall(
    const BabelUtils::SharedPtr<ClientSocket> &clientSocket,
    const std::shared_ptr<CallResponse> &resp,
    const ClientList &clientList
)
{
    for (const auto &target: clientList) {
        if (target->getUser() && target->getUser()->login == resp->getSender()) {
            std::cout << "ici" << std::endl;
            deleteConf(resp->getCallId());
            target->sendResponse(CallResponse::LeftCall(resp->getReceiver(), resp->getSender()));
            clientSocket->sendResponse(CallResponse::LeftCall(resp->getSender(), resp->getReceiver()));
            return;
        }
    }
    clientSocket->sendResponse(CallResponse::DisconnectedUser(resp->getSender(), resp->getReceiver()));
}

void CallManager::deleteConf(const uint16_t call_id)
{
    for (auto it = _confs.begin(); it != _confs.end(); it++) {
        if (it->getCallId() == call_id) {
            _confs.erase(it);
            return;
        }
    }
}

bool CallManager::updateConf(const uint16_t call_id, const std::string &ip, const std::string &port)
{
    for (auto &conf: _confs) {
        if (conf.getCallId() == call_id) {
            conf.setReceiver(ip, port);
            return true;
        }
    }
    return false;
}
