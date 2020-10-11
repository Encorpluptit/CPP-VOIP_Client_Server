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

Test(Common, FriendResponse_03)
{
    const AResponse::ResponseHeader hdr = {
        ._code = FriendResponse::ResponseCode::FriendAdded,
        ._responseType = AResponse::ResponseType::Friend,
        ._dataInfosSize = 0
    };
    FriendResponse test(hdr);

    ASSERT_BOOL(test.isOk(), false);

    ASSERT_INT(test.getResponseType(), AResponse::ResponseType::Friend);
    ASSERT_BOOL(test.getDescription().empty(), false);
    ASSERT_BOOL(test.describe_code().empty(), false);
    ASSERT_BOOL(test.describe_data().empty(), false);
    ASSERT_BOOL(test.describe_data_infos().empty(), false);
}

Test(Common, FriendResponse_login_too_long)
{
    const std::string sender = std::string(FriendResponse::MaxDataSize::Login + 1, '*');
    const std::string receiver = std::string(FriendResponse::MaxDataSize::FriendLogin, '*');

    cr_assert_throw(
        FriendResponse test(sender, receiver),
        BabelErrors::FriendResponse
    );
}

Test(Common, FriendResponse_friend_login_too_long)
{
    const std::string sender = std::string(FriendResponse::MaxDataSize::Login, '*');
    const std::string receiver = std::string(FriendResponse::MaxDataSize::FriendLogin + 1, '*');

    cr_assert_throw(
        FriendResponse test(sender, receiver),
        BabelErrors::FriendResponse
    );
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

Test(Common, FriendResponse_AddFriend)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::FriendAdded;

    auto friendClass = FriendResponse::AddFriend(login, friendLogin);
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

Test(Common, FriendResponse_NewFriendRequest)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::NewFriendshipRequested;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
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

Test(Common, FriendResponse_NewFriendRequest_poly)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::NewFriendshipRequested;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::NewFriendRequest(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_FriendRequestAccepted)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::AcceptFriendRequest;

    auto friendClass = FriendResponse::FriendRequestAccepted(login, friendLogin);
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

Test(Common, FriendResponse_FriendRequestDeclined)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::DeclineFriendRequest;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::FriendRequestDeclined(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_UserNotExist)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::UnknownUser;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::UserNotExist(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_DeleteFriendOK)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::FriendDeleted;

    auto friendClass = FriendResponse::DeleteFriendOK(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_DeleteFriendOK_poly)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::FriendDeleted;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::DeleteFriendOK(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_DeleteFriendRequest)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::RequestDeleteFriend;

    auto friendClass = FriendResponse::DeleteFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_FriendshipExist)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::FriendshipAlreadyExist;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::FriendshipExist(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_UnknownFriendship)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::FriendshipUnknown;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::UnknownFriendship(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}

Test(Common, FriendResponse_UnknownErrorOccured)
{
    const std::string login("ugo");
    const std::string friendLogin("dam");
    const AResponse::ResponseType type = AResponse::ResponseType::Friend;
    const FriendResponse::ResponseCode code = FriendResponse::ResponseCode::UnknownErrorOccur;

    auto friendClass = FriendResponse::NewFriendRequest(login, friendLogin);
    cr_assert_not_null(friendClass);
    auto test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    friendClass = FriendResponse::UnknownErrorOccured(test);
    cr_assert_not_null(friendClass);
    test = std::dynamic_pointer_cast<FriendResponse>(friendClass);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), FriendResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);
}
