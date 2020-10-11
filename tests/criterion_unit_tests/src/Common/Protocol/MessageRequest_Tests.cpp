//
// Created by encorpluptit on 10/11/20.
//

#include "tests_run.hpp"
#include "MessageResponse.hpp"
#include "ResponseError.hpp"

Test(Common, MessageResponse_00)
{
    const BabelNetwork::AResponse::ResponseHeader hdr = {
        ._code = BabelNetwork::MessageResponse::ResponseCode::RequestSendMessage,
        ._responseType = BabelNetwork::AResponse::ResponseType::Message,
        ._dataInfosSize = 0
    };
    BabelNetwork::MessageResponse test(hdr);

    ASSERT_INT(test.getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    ASSERT_BOOL(test.getDescription().empty(), false);
    ASSERT_BOOL(test.describe_code().empty(), false);
    ASSERT_BOOL(test.describe_data().empty(), false);
    ASSERT_BOOL(test.describe_data_infos().empty(), false);
}

Test(Common, MessageResponse_001)
{
    const BabelNetwork::AResponse::ResponseHeader hdr = {
        ._code = 500,
        ._responseType = BabelNetwork::AResponse::ResponseType::Message,
        ._dataInfosSize = 0
    };
    BabelNetwork::MessageResponse test(hdr);

    ASSERT_INT(test.getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    ASSERT_BOOL(test.getDescription().empty(), false);
    ASSERT_BOOL(test.describe_code().empty(), false);
    ASSERT_BOOL(test.describe_data().empty(), false);
    ASSERT_BOOL(test.describe_data_infos().empty(), false);
}

Test(Common, MessageResponse_01)
{
    const std::string user_1("dam");
    const std::string user_2("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse test(user_1, user_2, msg);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    cr_assert_str_eq(test.getSender(), user_1.c_str());
    cr_assert_str_eq(test.getReceiver(), user_2.c_str());
    cr_assert_str_eq(test.getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_02)
{
    const std::string user_1("dam");
    const std::string user_2("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse test(user_1, user_2, msg);


    const std::string login("toto");
    const std::string pass("tata");

    ASSERT_BOOL(test.encode(), true);
    char *dataByte = test.getDataByte();

    auto ptr = BabelNetwork::AResponse::getResponse(dataByte);
    cr_assert_not_null(ptr);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), test.getCode());

    std::memcpy(ptr->getDataByteDataInfos(), test.getDataByteDataInfos(), test.getDataInfosSize());
    ASSERT_BOOL(ptr->decode_data_infos(), true);
    std::memcpy(ptr->getDataByteBody(), test.getDataByteBody(), test.getDataSize());
    ASSERT_BOOL(ptr->decode_data(), true);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), user_1.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), user_2.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
    EXPECT_SIZET(ptr->getResponseSize(), test.getResponseSize());
    EXPECT_BOOL(ptr->isOk(), false);
}

Test(Common, MessageResponse_03)
{
    const std::string sender = std::string(BabelNetwork::MessageResponse::MaxDataSize::Sender + 1, '*');
    const std::string receiver = std::string(BabelNetwork::MessageResponse::MaxDataSize::Receiver, '*');
    const std::string msg = std::string(BabelNetwork::MessageResponse::MaxDataSize::MessageData, '*');

    cr_assert_throw(
        BabelNetwork::MessageResponse test(sender, receiver, msg),
        BabelErrors::MessageResponse
    );
}

Test(Common, MessageResponse_04)
{
    const std::string sender = std::string(BabelNetwork::MessageResponse::MaxDataSize::Sender, '*');
    const std::string receiver = std::string(BabelNetwork::MessageResponse::MaxDataSize::Receiver + 1, '*');
    const std::string msg = std::string(BabelNetwork::MessageResponse::MaxDataSize::MessageData, '*');

    cr_assert_throw(
        BabelNetwork::MessageResponse test(sender, receiver, msg),
        BabelErrors::MessageResponse
    );
}

Test(Common, MessageResponse_05)
{
    const std::string sender = std::string(BabelNetwork::MessageResponse::MaxDataSize::Sender, '*');
    const std::string receiver = std::string(BabelNetwork::MessageResponse::MaxDataSize::Receiver, '*');
    const std::string msg = std::string(BabelNetwork::MessageResponse::MaxDataSize::MessageData + 1, '*');

    cr_assert_throw(
        BabelNetwork::MessageResponse test(sender, receiver, msg),
        BabelErrors::MessageResponse
    );
}

Test(Common, MessageResponse_RequestMessageSend)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::RequestSendMessage;

    auto ptr = BabelNetwork::MessageResponse::RequestMessageSend(sender, receiver, msg);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_MessageReceive)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::ReceiveMessage;

    auto ptr = BabelNetwork::MessageResponse::MessageReceive(sender, receiver, msg);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_MessageReceive_poly)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::ReceiveMessage;

    auto lol = BabelNetwork::MessageResponse::RequestMessageSend(sender, receiver, msg);
    auto lol2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(lol);
    auto ptr = BabelNetwork::MessageResponse::MessageReceive(lol2);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_OkSendMessage)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::SendMessageOk;

    auto lol = BabelNetwork::MessageResponse::MessageReceive(sender, receiver, msg);
    auto lol2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(lol);
    auto ptr = BabelNetwork::MessageResponse::OkSendMessage(lol2);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_ReceiveMessageOk)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::ReceiveOk;

    auto ptr = BabelNetwork::MessageResponse::ReceiveMessageOk(sender, receiver);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
}

Test(Common, MessageResponse_UserNotFound)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::UnknownUser;

    auto lol = BabelNetwork::MessageResponse::MessageReceive(sender, receiver, msg);
    auto lol2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(lol);
    auto ptr = BabelNetwork::MessageResponse::UserNotFound(lol2);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}

Test(Common, MessageResponse_UnknownErrorAppend)
{
    const std::string sender("dam");
    const std::string receiver("ugo");
    const std::string msg("Coucou !");
    BabelNetwork::MessageResponse::ResponseCode code = BabelNetwork::MessageResponse::ResponseCode::UnknownError;

    auto lol = BabelNetwork::MessageResponse::MessageReceive(sender, receiver, msg);
    auto lol2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(lol);
    auto ptr = BabelNetwork::MessageResponse::UnknownErrorAppend(lol2);
    EXPECT_INT(ptr->getResponseType(), BabelNetwork::AResponse::ResponseType::Message);
    EXPECT_SIZET(ptr->getDataInfosSize(), BabelNetwork::MessageResponse::DataInfosSize);
    EXPECT_INT(ptr->getCode(), code);

    auto ptr2 = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(ptr);
    cr_assert_not_null(ptr2);
    cr_assert_str_eq(ptr2->getSender(), sender.c_str());
    cr_assert_str_eq(ptr2->getReceiver(), receiver.c_str());
    cr_assert_str_eq(ptr2->getMessageData(), msg.c_str());
}
