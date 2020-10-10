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
    const AResponse::ResponseHeader hdr = {
        ._code = UserResponse::ResponseCode::UnknownUserError,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 0
    };
    UserResponse test(hdr);

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::User);
    ASSERT_BOOL(test.getDescription().empty(), false);
}

Test(Common, UserResponse_04)
{
    const AResponse::ResponseHeader hdr = {
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
    const AResponse::ResponseHeader hdr = {
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
    const AResponse::ResponseHeader hdr = {
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
    const AResponse::ResponseHeader hdr = {
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
    const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');

    ASSERT_BOOL(test.setLogin(login), true);
}

Test(Common, UserResponse_09)
{
    const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    const std::string login = std::string(UserResponse::MaxDataSize::Login + 1, '*');

    ASSERT_BOOL(test.setLogin(login), false);
}

Test(Common, UserResponse_10)
{
    const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

    ASSERT_BOOL(test.setPassword(pass), true);
}

Test(Common, UserResponse_11)
{
    const AResponse::ResponseHeader hdr = {
        ._code = 40,
        ._responseType = AResponse::ResponseType::User,
        ._dataInfosSize = 50
    };
    UserResponse test(hdr);
    const std::string pass = std::string(UserResponse::MaxDataSize::Password + 1, '*');

    ASSERT_BOOL(test.setPassword(pass), false);
}

Test(Common, UserResponse_12)
{
    const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');
    const std::string pass = std::string(UserResponse::MaxDataSize::Password + 1, '*');

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
    const std::string login = std::string(UserResponse::MaxDataSize::Login, '*');
    const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

    cr_assert_no_throw(
        UserResponse test(login, pass),
        BabelErrors::UserResponse
    )
}

Test(Common, UserResponse_14)
{
    const std::string login = std::string(UserResponse::MaxDataSize::Login + 1, '*');
    const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');

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
    const std::string login("toto");
    const std::string pass("tata");

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
    const std::string login("toto");
    const std::string pass("tata");
    UserResponse test(login, pass);
    size_t sz = login.size() + pass.size() + AResponse::HeaderSize + UserResponse::DataInfosSize;

    ASSERT_SIZET(test.getResponseSize(), sz);
}

Test(Common, UserResponse_17)
{
    const AResponse::ResponseHeader hdr = {
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
    const AResponse::ResponseHeader hdr = {
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
    const std::string login("toto");
    const std::string pass("tata");

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
    const std::string login("toto");
    const std::string pass("tata");

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
    const std::string login("toto");
    const std::string pass("tata");

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

Test(Common, UserResponse_NewLoginRequest)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::RequestLogin;

    auto user = UserResponse::NewLoginRequest(login, pass);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    cr_assert_str_eq(test->getPassword(), pass.c_str());
}

Test(Common, UserResponse_LogoutRequest)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::RequestLogout;

    auto user = UserResponse::LogoutRequest(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
}

Test(Common, UserResponse_AccountCreationRequest)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::RequestAccountCreation;

    auto user = UserResponse::AccountCreationRequest(login, pass);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    cr_assert_str_eq(test->getPassword(), pass.c_str());
}

Test(Common, UserResponse_AccountDeletionRequest)
{
    const std::string login("toto");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::RequestAccountDeletion;

    auto user = UserResponse::AccountDeletionRequest(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_LoggedInOk)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::LoggedIn;

    auto user = UserResponse::LoggedInOk(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_LoggedOutOk)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::LoggedOut;

    auto user = UserResponse::LoggedOutOk(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_AccountCreatedOk)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::AccountCreated;

    auto user = UserResponse::AccountCreatedOk(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_AccountDeletedOk)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::AccountDeleted;

    auto user = UserResponse::AccountDeletedOk(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_UnknownError)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::UnknownUserError;

    auto user = UserResponse::UnknownError(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_BadLogin)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::WrongLogin;

    auto user = UserResponse::BadLogin(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_BadPassword)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::WrongPassword;

    auto user = UserResponse::BadPassword(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_LoginAlreadyUsed)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::LoginAlreadyTaken;

    auto user = UserResponse::LoginAlreadyUsed(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_AlreadyLog)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::AlreadyLoggedIn;

    auto user = UserResponse::AlreadyLog(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_RequestedDeletedAccount)
{
    const std::string login("toto");
    const std::string pass("tata");
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::RequestedAccountDeleted;

    auto user = UserResponse::RequestedDeletedAccount(login);
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    cr_assert_str_eq(test->getLogin(), login.c_str());
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}

Test(Common, UserResponse_ClientNotLogged)
{
    const AResponse::ResponseType type = AResponse::ResponseType::User;
    const UserResponse::ResponseCode code = UserResponse::ResponseCode::ClientLoggedOut;

    auto user = UserResponse::ClientNotLogged();
    cr_assert_not_null(user);
    auto test = std::dynamic_pointer_cast<UserResponse>(user);
    cr_assert_not_null(test);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), UserResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
    ASSERT_BOOL(std::string(test->getLogin()).empty(), true);
    ASSERT_BOOL(std::string(test->getPassword()).empty(), true);
}
