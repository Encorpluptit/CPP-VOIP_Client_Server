#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "cert-err58-cpp"
/*
** EPITECH PROJECT, 2020
** CPP_babel_2020 (Copyright (c) ENCORPLUPTIT on 7/10/20).
** File description:
** [Protocol_Tests.cpp]: Source file for Protocol_Tests.cpp feature.
*/

#include "tests_run.hpp"
#include "UserResponse.hpp"
#include "ResponseError.hpp"
using namespace BabelNetwork;

Test(Common, UserResponse_01)
{
    UserResponse test;

    ASSERT_BOOL(test.isOk(), false);
}

Test(Common, UserResponse_02)
{
    UserResponse test;

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_03)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = UserResponse::ResponseCode::UnknownUserError,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_04)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = UserResponse::ResponseCode::LoggedIn,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0,
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.isOk(), true);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_05)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 0,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 5
    };
    UserResponse test(hdr);

    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_06)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 0,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_07)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);

    ASSERT_INT(test.getCode(), hdr._code);
    ASSERT_SIZET(test.getDataInfosSize(), hdr._dataInfosSize);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_08)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    static const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');

    ASSERT_BOOL(test.setLogin(login), true);
}

Test(Common, UserResponse_09)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    static const std::string login = std::string(UserResponse::MaxDataSize::Login + 1, '*');

    ASSERT_BOOL(test.setLogin(login), false);
}

Test(Common, UserResponse_10)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    static const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

    ASSERT_BOOL(test.setPassword(pass), true);
}

Test(Common, UserResponse_11)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    static const std::string pass = std::string(UserResponse::MaxDataSize::Password + 1, '*');

    ASSERT_BOOL(test.setPassword(pass), false);
}

Test(Common, UserResponse_12)
{
    static const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');
    static const std::string pass = std::string(UserResponse::MaxDataSize::Password + 1, '*');

    cr_assert_throw(
        UserResponse test(login, pass),
        BabelErrors::UserResponse
        );
    try {
        UserResponse test(login, pass);
    } catch (const BabelErrors::UserResponse &e) {
        cr_assert_str_eq(e.what(), "login or password too long");
    }
}

Test(Common, UserResponse_13)
{
    static const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');
    static const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

    cr_assert_no_throw(
        UserResponse test(login, pass),
        BabelErrors::UserResponse
    )
}

Test(Common, UserResponse_14)
{
    static const std::string login = std::string(UserResponse::MaxDataSize::Login + 1, '*');
    static const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

    cr_assert_throw(
        UserResponse test(login, pass),
        BabelErrors::UserResponse
        );
    try {
        UserResponse test(login, pass);
    } catch (const BabelErrors::UserResponse &e) {
        cr_assert_str_eq(e.what(), "login or password too long");
    }
}

Test(Common, UserResponse_15)
{
    static const std::string login("toto");
    static const std::string pass("tata");

    UserResponse test(login, pass);
    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    cr_assert_str_eq(test.getLogin(), login.c_str());
    cr_assert_str_eq(test.getPassword(), pass.c_str());
}

Test(Common, UserResponse_16)
{
    static const std::string login("toto");
    static const std::string pass("tata");
    UserResponse test(login, pass);
    size_t sz = login.size() + pass.size() + AResponse::HeaderSize + UserResponse::DataInfosSize;

    ASSERT_SIZET(test.getResponseSize(), sz);
}

Test(Common, UserResponse_17)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = UserResponse::ResponseCode::AccountCreated,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0,
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.isOk(), true);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_18)
{
    static const AResponse::ResponseHeader hdr = {
        ._code = UserResponse::ResponseCode::AccountDeleted,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0,
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.isOk(), true);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
}

Test(Common, UserResponse_19)
{
    static const std::string login("toto");
    static const std::string pass("tata");

    UserResponse test(login, pass);
    auto ptr = test.get_shared_from_this();

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    ASSERT_INT(ptr->getResponseType(), test.getResponseType());
    ASSERT_INT(ptr->getCode(), test.getCode());
}

Test(Common, UserResponse_20)
{
    static const std::string login("toto");
    static const std::string pass("tata");

    UserResponse test(login, pass);
    test.setCode(UserResponse::ResponseCode::LoggedIn);
    auto ptr = test.get_shared_from_this();

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    ASSERT_INT(ptr->getResponseType(), AResponse::ResponseType::User);
    ASSERT_INT(ptr->getCode(), test.getCode());
}

Test(Common, UserResponse_21)
{
    static const std::string login("toto");
    static const std::string pass("tata");

    UserResponse test(login, pass);
    test.setCode(UserResponse::ResponseCode::LoggedIn);
    ASSERT_BOOL(test.encode(), true);
    char *dataByte = test.getDataByte();
    auto ptr = AResponse::getResponse(dataByte);

    cr_assert_not_null(ptr);
    ASSERT_BOOL(ptr->decode_data_infos(), true);
    ASSERT_BOOL(ptr->decode_data(), true);

    EXPECT_INT(ptr->getResponseType(), AResponse::ResponseType::User);
    EXPECT_SIZET(ptr->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), test.getCode());
}

#pragma clang diagnostic pop