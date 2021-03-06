/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [CallResponse.hpp]: Header file for CallResponse feature.
*/

#ifndef CPP_BABEL_2020_CALL_RESPONSE_HPP
#define CPP_BABEL_2020_CALL_RESPONSE_HPP

#include <map>
#include "AResponse.hpp"

namespace BabelNetwork {
    class CallResponse final : virtual public BabelNetwork::AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            CallStarted = 200,
            RequestCall = 201,
            CallLeft = 202,
            RequestEndCall = 203,
            IncomingCall = 204,
            CallAccepted = 205,

            CallRefused = 270,
            UserDisconnected = 271,
            UnknownError = 272,
        };

    public:
        enum MaxDataSize {
            Sender = 128,
            Receiver = 128,
            Ip = 20,
            Port = 5
        };

        /* <- Class Structure -> */
    public:
        using Data = struct DataStruct {
            char sender[MaxDataSize::Sender];
            char receiver[MaxDataSize::Receiver];
            time_t timestamp;
            uint16_t callId;
            char ip[MaxDataSize::Sender];
            char port[MaxDataSize::Receiver];
        };
        static const size_t DataSize = sizeof(Data);

        /* <- Class Structure -> */
    public:
        using DataInfos = struct DataInfosStruct {
            uint16_t _senderSize;
            uint16_t _receiverSize;
            uint8_t _timestampSize;
            uint8_t _callIdSize;
            uint8_t _ipSize;
            uint8_t _portSize;
        };
        static const size_t DataInfosSize = sizeof(DataInfos);

        /* <- Class Variables -> */
    public:
        static const size_t MaxResponseSize = HeaderSize + DataInfosSize + DataSize;

        /* <- Constructor - Destructor -> */
    public:
        explicit CallResponse(const ResponseHeader &headerResponse);

        CallResponse(const std::string &sender, const std::string &receiver);

        CallResponse(
            const std::string &sender,
            const std::string &receiver,
            const std::string &ip,
            const std::string &port
        );

        ~CallResponse() = default;

        /* <- Encode / Decode Methods -> */
    public:
        [[nodiscard]] bool encode() noexcept final;

        [[nodiscard]] bool decode_header() noexcept final;

        [[nodiscard]] bool decode_data_infos() noexcept final;

        [[nodiscard]] bool decode_data() noexcept final;

        /* <- Get Sizes Methods -> */
    public:
        [[nodiscard]] size_t getResponseSize() const noexcept final;

        [[nodiscard]] size_t getDataSize() const noexcept final;

        /* <- Request related Methods -> */
    public:
        [[nodiscard]] bool isOk() noexcept final;

        [[nodiscard]] std::string describe_code() const noexcept final;

        [[nodiscard]] std::string describe_data() const noexcept final;

        [[nodiscard]] std::string describe_data_infos() const noexcept final;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] char *getDataByte() noexcept final;

        [[nodiscard]] char *getDataByteDataInfos() const noexcept final;

        [[nodiscard]] char *getDataByteBody() const noexcept final;

        [[nodiscard]] const std::string &getDescription() const noexcept final
        {
            return _description;
        };

        [[nodiscard]] bool setSender(const std::string &sender) noexcept;

        [[nodiscard]] bool setReceiver(const std::string &receiver) noexcept;

        [[nodiscard]] bool setTimestamp() noexcept;

        [[nodiscard]] bool setCallId(uint16_t call_id) noexcept;

        [[nodiscard]] bool setIp(const std::string &ip) noexcept;

        [[nodiscard]] bool setPort(const std::string &port) noexcept;

        [[nodiscard]] const char *getSender() const noexcept { return _data.sender; };

        [[nodiscard]] const char *getReceiver() const noexcept { return _data.receiver; };

        [[nodiscard]] uint16_t getCallId() const noexcept { return _data.callId; };

        [[nodiscard]] time_t getTimestamp() const noexcept { return _data.timestamp; };

        [[nodiscard]] const char *getIp() const noexcept { return _data.ip; };

        [[nodiscard]] const char *getPort() const noexcept { return _data.port; };

        /* <- Attributes -> */
    private:
        const std::string _description = "Call Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
        Data _data{};

        /* <- Formatted Response -> */
    public:
        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> NewCallStarted(
            const std::string &sender,
            const std::string &receiver,
            const std::string &ip,
            const std::string &port,
            uint16_t call_id
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> CallRequest(
            const std::string &sender,
            const std::string &receiver,
            const std::string &ip,
            const std::string &port
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> LeftCall(
            const std::string &sender,
            const std::string &receiver
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> EndCallRequest(
            const std::shared_ptr<BabelNetwork::CallResponse> &resp
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> CallIncoming(
            const std::shared_ptr<CallResponse> &resp,
            uint16_t call_id
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> AcceptCall(
            const std::shared_ptr<BabelNetwork::CallResponse> &resp,
            const std::string &ip,
            uint16_t port
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> RefusedCall(
            const std::shared_ptr<BabelNetwork::CallResponse> &response
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> DisconnectedUser(
            const std::string &sender,
            const std::string &receiver
        );

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse> UnknownErrorOccured(
            const std::shared_ptr<BabelNetwork::CallResponse> &response
        );

        /* <- Stringify Code -> */
    private:
        const std::map<ResponseCode, std::string> codeString = {
            {CallStarted,      "Call Started"},
            {RequestCall,      "Call Requested"},
            {CallLeft,         "Call Left"},
            {RequestEndCall,   "End Call Requested"},
            {IncomingCall,     "Incoming Call"},
            {CallAccepted,     "Call Accepted"},
            {CallRefused,      "Call Refused"},
            {UserDisconnected, "[CALL] User Disconnected"}
        };
    };
}

#endif /* CPP_BABEL_2020_CALL_RESPONSE_HPP */
