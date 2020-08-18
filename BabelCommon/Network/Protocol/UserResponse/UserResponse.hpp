/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [UserResponse.hpp]: Header file for UserResponse feature.
*/

#ifndef CPP_BABEL_2020_CONNECTIONRESPONSE_HPP
#define CPP_BABEL_2020_CONNECTIONRESPONSE_HPP

#include "AResponse.hpp"

namespace BabelNetwork {
    class UserResponse final : virtual public AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            ConnectionOk = 100,
            LoginOk = 210,
            RequestLogin = 211,
            AccountCreated = 220,
            AccountDeleted = 230,

        };
    private:
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

        [[nodiscard]] const std::string &getDescription() const noexcept final {
            return _description;
        };

        [[nodiscard]] bool setLogin(const std::string &login) noexcept;

        [[nodiscard]] bool setPassword(const std::string &password) noexcept;

        [[nodiscard]] const char *getLogin() const noexcept { return _data.login; };

        [[nodiscard]] const char *getPassword() const noexcept { return _data.password; };

    private:
        const std::string _description = "User Related Request";
        char _data_byte[MaxResponseSize] = {0};
        DataInfos _dataInfos{};
        Data _data{};
    };
}

#endif /* CPP_BABEL_2020_CONNECTIONRESPONSE_HPP */
