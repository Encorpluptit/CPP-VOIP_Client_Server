//
// Created by encorpluptit on 10/10/20.
//

#include "tests_run.hpp"
#include "FriendResponse.hpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

Test(Common, FriendResponse_01)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");

    FriendResponse test(login, friendLogin);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    cr_assert_str_eq(test.getLogin(), login.c_str());
    cr_assert_str_eq(test.getFriendLogin(), friendLogin.c_str());
}

Test(Common, FriendResponse_02)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");

    FriendResponse test{};

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);
}

Test(Common, FriendResponse_RequestFriend)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::RequestAddFriend;

    auto friendClass = FriendResponse::RequestFriend(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}
