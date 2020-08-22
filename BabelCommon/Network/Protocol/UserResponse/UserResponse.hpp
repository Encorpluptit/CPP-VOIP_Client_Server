/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [UserResponse.hpp]: Header file for UserResponse feature.
*/

#ifndef CPP_BABEL_2020_USER_RESPONSE_HPP
#define CPP_BABEL_2020_USER_RESPONSE_HPP

#include "AResponse.hpp"

namespace BabelNetwork {
    class UserResponse final : virtual public AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            LoggedIn = 200,
            RequestLogin = 201,
            LoggedOut = 202,
            RequestLogout = 203,

            AccountCreated = 210,
            RequestAccountCreation = 211,
            AccountDeleted = 212,
            RequestAccountDeletion = 213,

            UnknownUserError = 270,
            WrongLogin = 271,
            WrongPassword = 272,
            RequestedAccountDeleted = 273, /* ? */
            LoginAlreadyTaken = 273,
            AlreadyLoggedIn = 274,
        };
    public:
        enum MaxDataSize {
            Login = 128,
            Password = 128
        };

        /* <- Class Structure -> */
    public:
        using Data = struct __attribute__((packed)) DataStruct {
            char login[MaxDataSize::Login];
            char password[MaxDataSize::Password];
        };
        static const size_t DataSize = sizeof(Data);

        /* <- Class Structure -> */
    public:
        using DataInfos = struct __attribute__((packed)) DataInfosStruct {
            uint16_t _loginSize;
            uint16_t _passwordSize;
        };
        static const size_t DataInfosSize = sizeof(DataInfos);

        /* <- Class Variables -> */
    public:
        static const size_t MaxResponseSize = HeaderSize + DataInfosSize + DataSize;

        /* <- Constructor - Destructor -> */
    public:
        UserResponse() : AResponse()
        {
            _header._responseType = User;
            _header._dataInfosSize = DataInfosSize;
        };

        explicit UserResponse(const ResponseHeader &headerResponse);

        UserResponse(const std::string &login, const std::string &password);

        ~UserResponse() = default;

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

        [[nodiscard]] bool setLogin(const std::string &login) noexcept;

        [[nodiscard]] bool setPassword(const std::string &password) noexcept;

        [[nodiscard]] const char *getLogin() const noexcept { return _data.login; };

        [[nodiscard]] const char *getPassword() const noexcept { return _data.password; };

        [[nodiscard]] const std::string &getDescription() const noexcept final
        {
            return _description;
        };

    private:
        const std::string _description = "User Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
        Data _data{};

    public:
        [[nodiscard]] static std::shared_ptr<AResponse> NewLoginRequest(const std::string &login, const std::string &password);
        [[nodiscard]] static std::shared_ptr<AResponse> AccountCreationRequest(const std::string &login, const std::string &password);
        [[nodiscard]] static std::shared_ptr<AResponse> LogoutRequest(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> AccountDeletionRequest(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> LoggingInOk(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> LoggedOutOk(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> AccountDeletedOk(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> UnknowUser(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> BadLogin(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> BadPassword(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> LoginUse(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> AlreadyLog(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> AccountCreatedOk(const std::string &login);
        [[nodiscard]] static std::shared_ptr<AResponse> RequestedDeletedAccount(const std::string &login);
    };
}

#endif /* CPP_BABEL_2020_USER_RESPONSE_HPP */
