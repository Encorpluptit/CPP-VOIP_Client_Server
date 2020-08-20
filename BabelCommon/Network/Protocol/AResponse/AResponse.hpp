/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/7/20).
** File description:
** [AResponse.hpp]: Header file for AResponse feature.
*/

#ifndef CPP_BABEL_2020_ARESPONSE_HPP
#define CPP_BABEL_2020_ARESPONSE_HPP

#include <string>
#include <cstring>
#include <ostream>
#include <memory>

namespace BabelNetwork {

    class AResponse {
        /* <- Class Enum -> */
    public:
        enum ResponseCode {
            UnknownError = 1000
        };

        /* <- Class Enum -> */
    public:
        enum ResponseType {
            UnknownType,
            User,
            Call,
            Friend,
            Message
        };

        /* <- Class Structure -> */
    public:
        using ResponseHeader = struct __attribute__((packed)) Response {
            uint16_t _code;
            ResponseType _responseType;
            size_t _dataInfosSize;
        };
        static const size_t HeaderSize = sizeof(ResponseHeader);

        /* <- Constructor - Destructor -> */
    public:
        AResponse() = default;

        explicit AResponse(const ResponseHeader &headerResponse);

        AResponse(const AResponse &other);

        ~AResponse() = default;


        /* <- Operators -> */
    public:
        friend std::ostream &operator<<(std::ostream &os, const AResponse &response);

        /* <- Static Methods -> */
    public:
        [[nodiscard]] static std::shared_ptr<AResponse> getResponse(const char *headerBuffer);

        /* <- Encode / Decode Methods -> */
    public:
        [[nodiscard]] virtual bool encode() noexcept = 0;

        [[nodiscard]] virtual bool decode_header() noexcept = 0;

        [[nodiscard]] virtual bool decode_data_infos() noexcept = 0;

        [[nodiscard]] virtual bool decode_data() noexcept = 0;


        /* <- Request related Methods -> */
    public:
        [[nodiscard]] virtual bool isOk() noexcept = 0;

        [[nodiscard]] std::string serialize() const noexcept;

        [[nodiscard]] virtual std::string serialize_data_infos() const noexcept = 0;

        [[nodiscard]] virtual std::string serialize_data() const noexcept = 0;

        /* <- Get Sizes Methods -> */
    public:
        [[nodiscard]] virtual size_t getResponseSize() const noexcept = 0;

        [[nodiscard]] virtual size_t getDataSize() const noexcept = 0;

        /* <- Getters / Setters -> */
    public:
        [[nodiscard]] uint16_t getCode() const noexcept;

        void setCode(uint16_t code) noexcept;

        [[nodiscard]] virtual std::shared_ptr<AResponse> get_shared_from_this() const = 0;

        [[nodiscard]] size_t getDataInfosSize() const noexcept;

        [[nodiscard]] ResponseType getResponseType() const;

        [[nodiscard]] virtual char *getDataByteDataInfos() const noexcept = 0;

        [[nodiscard]] virtual char *getDataByteBody() const noexcept = 0;

        [[nodiscard]] virtual char *getDataByte() noexcept = 0;

        [[nodiscard]] virtual const std::string &getDescription() const noexcept = 0;


        /* <- Attributes -> */
    protected:
        ResponseHeader _header{};
    };

    /* <- Operators -> */
    std::ostream &operator<<(std::ostream &os, const AResponse &response);
}

#endif /* CPP_BABEL_2020_ARESPONSE_HPP */
