//
// Created by encorpluptit on 10/11/20.
//

#include "tests_run.hpp"
#include "MessageResponse.hpp"
#include "ResponseError.hpp"

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
}
