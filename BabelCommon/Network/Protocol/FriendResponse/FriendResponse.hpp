/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [FriendResponse.hpp]: Header file for FriendResponse feature.
*/

#ifndef CPP_BABEL_2020_FRIEND_RESPONSE_HPP
#define CPP_BABEL_2020_FRIEND_RESPONSE_HPP

#include <map>
#include "AResponse.hpp"

namespace BabelNetwork {
    class FriendResponse final : virtual public AResponse {

        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            RequestAddFriend = 300,
            FriendAdded = 301,
            NewFriendshipRequested = 302,
            AcceptFriendRequest = 303,
            DeclineFriendRequest = 304,
            RequestDeleteFriend = 305,
            FriendDeleted = 306,

            FriendshipAlreadyExist = 350,
            FriendshipUnknown = 351,
            UnknownUser = 352,
            UnknownErrorOccur = 354,
        };

    private:
        enum MaxDataSize {
            Login = 128,
            FriendLogin = 128
        };

        /* <- Class Structure -> */
    public:
        using Data = struct __attribute__((packed)) DataStruct {
            char login[MaxDataSize::Login];
            char FriendLogin[MaxDataSize::FriendLogin];
        };
        static const size_t DataSize = sizeof(Data);

        /* <- Class Structure -> */
    public:
        using DataInfos = struct __attribute__((packed)) DataInfosStruct {
            uint16_t _loginSize;
            uint16_t _friendLoginSize;
        };
        static const size_t DataInfosSize = sizeof(DataInfos);

        /* <- Class Variables -> */
    public:
        static const size_t MaxResponseSize = HeaderSize + DataInfosSize + DataSize;

        /* <- Constructor - Destructor -> */
    public:
        FriendResponse() : AResponse()
        {
            _header._responseType = Friend;
            _header._dataInfosSize = DataInfosSize;
        };

        explicit FriendResponse(const ResponseHeader &headerResponse);

        FriendResponse(const std::string &login, const std::string &FriendLogin);

        ~FriendResponse() = default;

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
        [[nodiscard]] std::shared_ptr<AResponse> get_shared_from_this() const noexcept final;

        [[nodiscard]] char *getDataByte() noexcept final;

        [[nodiscard]] char *getDataByteDataInfos() const noexcept final;

        [[nodiscard]] char *getDataByteBody() const noexcept final;

        [[nodiscard]] const std::string &getDescription() const noexcept final
        {
            return _description;
        };

        [[nodiscard]] bool setLogin(const std::string &login) noexcept;

        [[nodiscard]] bool setFriendLogin(const std::string &FriendLogin) noexcept;

        [[nodiscard]] const char *getLogin() const noexcept { return _data.login; };

        [[nodiscard]] const char *getFriendLogin() const noexcept { return _data.FriendLogin; };

    private:
        const std::string _description = "Friend Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
        Data _data{};

        /* <- Formatted Response -> */
    public:
        [[nodiscard]] static std::shared_ptr<AResponse>
        RequestFriend(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        AddFriend(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        NewFriendRequest(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        NewFriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        FriendRequestAccepted(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        FriendRequestDeclined(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        DeleteFriendRequest(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        UserNotExist(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        DeleteFriendOK(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        DeleteFriendOK(const std::string &login, const std::string &friendLogin);

        [[nodiscard]] static std::shared_ptr<AResponse>
        FriendshipExist(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        UnknownFriendship(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        [[nodiscard]] static std::shared_ptr<AResponse>
        UnknownErrorOccured(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        /* <- Stringify Code -> */
    private:
        const std::map<ResponseCode, std::string> codeString = {
            {RequestAddFriend,       "Request AddFriend"},
            {FriendAdded,            "Friend Added"},
            {NewFriendshipRequested, "NewFriendship Requested"},
            {AcceptFriendRequest,    "AcceptFriend Request"},
            {DeclineFriendRequest,   "Decline FriendRequest"},
            {RequestDeleteFriend,    "Request DeleteFriend"},
            {FriendDeleted,          "Friend Deleted"},
            {FriendshipAlreadyExist, "Friendship AlreadyExist"},
            {FriendshipUnknown,      "Friendship Unknown"},
            {UnknownUser,            "Unknown User"},
            {UnknownErrorOccur,      "Unknown ErrorOccur"},
        };
    };
}

#endif /* CPP_BABEL_2020_FRIEND_RESPONSE_HPP */
