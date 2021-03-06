/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [MessageResponse.hpp]: Header file for MessageResponse feature.
*/

#ifndef CPP_BABEL_2020_MESSAGE_RESPONSE_HPP
#define CPP_BABEL_2020_MESSAGE_RESPONSE_HPP

#include <map>
#include <ctime>
#include "AResponse.hpp"

namespace BabelNetwork {
    class MessageResponse final : virtual public BabelNetwork::AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            RequestSendMessage = 401,
            SendMessageOk = 402,
            ReceiveMessage = 403,
            ReceiveOk = 404,

            UnknownUser = 450,
            UnknownError = 460
        };

    public:
        enum MaxDataSize {
            Sender = 128,
            Receiver = 128,
            MessageData = 512
        };

        /* <- Class Structure -> */
    public:
        struct Data {
            char sender[MaxDataSize::Sender];
            char receiver[MaxDataSize::Receiver];
            char messageData[MaxDataSize::MessageData];
            std::time_t timestamp;
        };
        static const size_t DataSize = sizeof(Data);

        /* <- Class Structure -> */
    public:
        using DataInfos = struct DataInfosStruct {
            uint16_t _senderSize;
            uint16_t _receiverSize;
            uint16_t _messageDataSize;
            uint8_t _timestampSize;
        };
        static const size_t DataInfosSize = sizeof(DataInfos);

        /* <- Class Variables -> */
    public:
        static const size_t MaxResponseSize = HeaderSize + DataInfosSize + DataSize;

        /* <- Constructor - Destructor -> */
    public:
        MessageResponse() : BabelNetwork::AResponse()
        {
            _header._responseType = Message;
            _header._dataInfosSize = DataInfosSize;
        };

        explicit MessageResponse(const ResponseHeader &headerResponse);

        MessageResponse(const std::string &sender, const std::string &receiver, const std::string &messageData);

        ~MessageResponse() = default;

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

        [[nodiscard]] bool setTimestamp() noexcept;

        [[nodiscard]] bool setReceiver(const std::string &receiver) noexcept;

        [[nodiscard]] bool setMessageData(const std::string &messageData) noexcept;

        [[nodiscard]] const char *getSender() const noexcept { return _data.sender; };

        [[nodiscard]] const char *getReceiver() const noexcept { return _data.receiver; };

        [[nodiscard]] const char *getMessageData() const noexcept { return _data.messageData; };

        [[nodiscard]] const time_t & getTimestamp() const noexcept { return _data.timestamp; };

        /* <- Attributes -> */
    private:
        const std::string _description = "Message Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
        Data _data{};

        /* <- Formatted Response -> */
    public:
        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        RequestMessageSend(const std::string &sender, const std::string &receiver, const std::string &messageData);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        OkSendMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        MessageReceive(const std::string &sender, const std::string &receiver, const std::string &messageData);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        MessageReceive(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        ReceiveMessageOk(const std::string &sender, const std::string &receiver);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        UserNotFound(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

        [[nodiscard]] static std::shared_ptr<BabelNetwork::AResponse>
        UnknownErrorAppend(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

        /* <- Stringify Code -> */
    private:
        const std::map<ResponseCode, std::string> codeString = {
            {RequestSendMessage, "Requested Send Message"},
            {SendMessageOk,      "Send Message Ok"},
            {ReceiveMessage,     "Receive Message"},
            {ReceiveOk,          "Receive Ok"},
            {UnknownUser,        "Unknown User"},
        };
    };
}

#endif /* CPP_BABEL_2020_MESSAGE_RESPONSE_HPP */
