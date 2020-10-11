//
// Created by hobbit on 10/10/20.
//

#include <iostream>
#include "tests_run.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

Test(Common, AResponse_01)
{
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::FriendAdded,
        ._responseType = AResponse::ResponseType::UnknownType,
        ._dataInfosSize = 0
    };
    char test[sizeof(hdr)];

    std::memcpy(test, &hdr, sizeof(hdr));
    cr_assert_null(AResponse::getResponse(test));
}

Test(Common, AResponse_02)
{
    AResponse::ResponseType type = AResponse::ResponseType::User;
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::UnknownUser,
        ._responseType = type,
        ._dataInfosSize = 0
    };
    char header[sizeof(hdr)];

    std::memcpy(header, &hdr, sizeof(hdr));
    auto test = AResponse::getResponse(header);
    ASSERT_INT(test->getResponseType(), type);
    ASSERT_BOOL(test->describe().empty(), false);
    ASSERT_SIZET(test->getDataInfosSize(), hdr._dataInfosSize);
    ASSERT_SIZET(test->getResponseHeader()._dataInfosSize, hdr._dataInfosSize);
}

Test(Common, AResponse_03)
{
    AResponse::ResponseType type = AResponse::ResponseType::Call;
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::UnknownUser,
        ._responseType = type,
        ._dataInfosSize = 0
    };
    char header[sizeof(hdr)];

    std::memcpy(header, &hdr, sizeof(hdr));
    auto test = AResponse::getResponse(header);
    ASSERT_INT(test->getResponseType(), type);
}

Test(Common, AResponse_04, .init=redirect_all_std)
{
    AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::UnknownUser,
        ._responseType = type,
        ._dataInfosSize = 0
    };
    char header[sizeof(hdr)];

    std::memcpy(header, &hdr, sizeof(hdr));
    auto test = AResponse::getResponse(header);
    ASSERT_INT(test->getResponseType(), type);
    std::cout << test << std::endl;
}

Test(Common, AResponse_05)
{
    AResponse::ResponseType type = AResponse::ResponseType::Message;
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::UnknownUser,
        ._responseType = type,
        ._dataInfosSize = 0
    };
    char header[sizeof(hdr)];

    std::memcpy(header, &hdr, sizeof(hdr));
    auto test = AResponse::getResponse(header);
    ASSERT_INT(test->getResponseType(), type);
}
