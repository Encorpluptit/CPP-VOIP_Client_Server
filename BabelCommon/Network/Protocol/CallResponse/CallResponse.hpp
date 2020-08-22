/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [CallResponse.hpp]: Header file for CallResponse feature.
*/

#ifndef CPP_BABEL_2020_CALL_RESPONSE_HPP
#define CPP_BABEL_2020_CALL_RESPONSE_HPP

#include "AResponse.hpp"

namespace BabelNetwork {
    class CallResponse final : virtual public AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            CallStarted = 300,
            RequestCall = 301,
            CallLeft = 302,
            RequestEndCall = 303,
            IncomingCall = 304,
            CallAccepted = 305,

            CallRefused = 370,
            UserDisconnected = 371,
        };

    private:
        enum MaxDataSize {
            Sender = 128,
            Receiver = 128
        };

        /* <- Class Structure -> */
    public:
        using Data = struct __attribute__((packed)) DataStruct {
            char sender[MaxDataSize::Sender];
            char receiver[MaxDataSize::Receiver];
            time_t timestamp;
            uint16_t callId;
        };
        static const size_t DataSize = sizeof(Data);

        /* <- Class Structure -> */
    public:
        using DataInfos = struct __attribute__((packed)) DataInfosStruct {
            uint16_t _senderSize;
            uint16_t _receiverSize;
            uint8_t _timestampSize;
            uint8_t _callIdSize;
        };
        static const size_t DataInfosSize = sizeof(DataInfos);

        /* <- Class Variables -> */
    public:
        static const size_t MaxResponseSize = HeaderSize + DataInfosSize + DataSize;

        /* <- Constructor - Destructor -> */
    public:
        explicit CallResponse(const ResponseHeader &headerResponse);

        CallResponse(const std::string &sender, const std::string &receiver);

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

//        [[nodiscard]] size_t getMaxResponseSize() const noexcept final {
//            return MaxResponseSize;
//        };

        /* <- Request related Methods -> */
    public:
        [[nodiscard]] bool isOk() noexcept final;

        [[nodiscard]] std::string serialize_data() const noexcept final;

        [[nodiscard]] std::string serialize_data_infos() const noexcept final;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] std::shared_ptr<AResponse> get_shared_from_this() const noexcept final;

        [[nodiscard]] char *getDataByte() noexcept final;

        [[nodiscard]] char *getDataByteDataInfos() const noexcept final;

        [[nodiscard]] char *getDataByteBody() const noexcept final;

        [[nodiscard]] const std::string &getDescription() const noexcept final {
            return _description;
        };

        [[nodiscard]] bool setSender(const std::string &sender) noexcept;

        [[nodiscard]] bool setReceiver(const std::string &receiver) noexcept;

        [[nodiscard]] bool setTimestamp() noexcept;

        [[nodiscard]] bool setCallId(uint16_t call_id) noexcept;

        [[nodiscard]] const char *getSender() const noexcept { return _data.sender; };

        [[nodiscard]] const char *getReceiver() const noexcept { return _data.receiver; };

        [[nodiscard]] uint16_t getCallId() const noexcept { return _data.callId; };

        [[nodiscard]] time_t getTimestamp() const noexcept { return _data.timestamp; };

    private:
        const std::string _description = "Call Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
//        DataInfos _dataInfos{0,0, sizeof(time_t), sizeof(uint16_t)};
        Data _data{};

    public:
        [[nodiscard]] static std::shared_ptr<AResponse> NewCallStarted(const std::string &sender, const std::string &receiver, uint16_t call_id);
        [[nodiscard]] static std::shared_ptr<AResponse> CallRequest(const std::string &sender, const std::string &receiver);
        [[nodiscard]] static std::shared_ptr<AResponse> LeftCall(const std::string &sender, const std::string &receiver, uint16_t call_id);
        [[nodiscard]] static std::shared_ptr<AResponse> EndCallRequest(const std::string &sender, const std::string &receiver);
        [[nodiscard]] static std::shared_ptr<AResponse> CallIncoming(const std::string &sender, const std::string &receiver, uint16_t call_id);
        [[nodiscard]] static std::shared_ptr<AResponse> AcceptCall(const std::string &sender, const std::string &receiver);
        [[nodiscard]] static std::shared_ptr<AResponse> RefusedCall(const std::string &sender, const std::string &receiver);
        [[nodiscard]] static std::shared_ptr<AResponse> DisconnectedUser(const std::string &sender, const std::string &receiver);
    };
}

#endif /* CPP_BABEL_2020_CALL_RESPONSE_HPP */
