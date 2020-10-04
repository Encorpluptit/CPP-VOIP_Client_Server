//
// Created by encorpluptit on 9/21/20.
//

#ifndef CPP_BABEL_2020_CALLMANAGER_HPP
#define CPP_BABEL_2020_CALLMANAGER_HPP

#include "Listener.hpp"
#include "Logger.hpp"
#include "CallResponse.hpp"
#include "Database.hpp"

namespace BabelServer {

    class Conference {
        /* <- Constructor - Destructor -> */
    public:
        explicit Conference(
            uint16_t id,
            const std::string &senderIp,
            const std::string &senderPort
        ) : _call_id(id), _sender(senderIp, senderPort) {};

        ~Conference() = default;

        /* <- Public Methods -> */
    public:
        void setReceiver(
            const std::string &receiverIp,
            const std::string &receiverPort
        )
        {
            _receiver.first = receiverIp;
            _receiver.second = receiverPort;
        }

        const uint16_t &getCallId() const { return _call_id; }

        const std::string &getSenderIp() const { return _sender.first; }

        const std::string &getSenderPort() const { return _sender.second; }

        const std::string &getReceiverIp() const { return _receiver.first; }

        const std::string &getReceiverPort() const { return _receiver.second; }

        /* <- Attributes -> */
    private:
        uint16_t _call_id;
        std::pair<std::string, std::string> _sender;
        std::pair<std::string, std::string> _receiver;
    };

    class CallManager {
        using CallManagerMethodProt = void(
            CallManager *,
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &,
            const BabelNetwork::ClientList &
        );
        using CallResponseFPtr = std::tuple<BabelNetwork::CallResponse::ResponseCode, std::function<CallManagerMethodProt>>;

        /* <- Constructor - Destructor -> */
    public:
        explicit CallManager(BabelUtils::Logger &logger) : _logger(logger) {};

        ~CallManager() = default;

        /* <- Private Methods -> */
    private:
        void requestCall(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &response,
            const BabelNetwork::ClientList &clientList);

        void refuseCall(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &response,
            const BabelNetwork::ClientList &clientList
        );

        void acceptCall(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &resp,
            const BabelNetwork::ClientList &clientList
        );

        void endCall(
            const BabelUtils::SharedPtr<BabelNetwork::ClientSocket> &clientSocket,
            const std::shared_ptr<BabelNetwork::CallResponse> &resp,
            const BabelNetwork::ClientList &clientList
        );

        void deleteConf(uint16_t call_id);

        [[nodiscard]] bool updateConf(uint16_t call_id, const std::string &ip, const std::string &port);

        /* <- Private Methods -> */
    private:

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] const std::vector<CallResponseFPtr> &getCallResponsePtrTab() const;

        void incrementCallId() { _call_id += 1; }

        [[nodiscard]] uint16_t getCallId() const { return _call_id; }


        /* <- Attributes -> */
    private:
        BabelUtils::Logger &_logger;
        uint16_t _call_id = 1;
        const std::vector<std::tuple<BabelNetwork::CallResponse::ResponseCode, std::function<CallManagerMethodProt>>> CallResponsePtrTab = {
            {BabelNetwork::CallResponse::ResponseCode::RequestCall,    &CallManager::requestCall},
            {BabelNetwork::CallResponse::ResponseCode::CallRefused,    &CallManager::refuseCall},
            {BabelNetwork::CallResponse::ResponseCode::CallAccepted,   &CallManager::acceptCall},
            {BabelNetwork::CallResponse::ResponseCode::RequestEndCall, &CallManager::endCall},
        };
        std::vector<Conference> _confs{};
    };

}
#endif //CPP_BABEL_2020_CALLMANAGER_HPP
