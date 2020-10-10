//
// Created by encorpluptit on 9/23/20.
//

#include "tests_run.hpp"
#include "CallResponse.hpp"
#include "ResponseError.hpp"

using namespace BabelNetwork;

Test(Common, CallResponse_01)
{
    const std::string sender("ugo");
    const std::string receiver("dam");

    CallResponse test(sender, receiver);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    cr_assert_str_eq(test.getSender(), sender.c_str());
    cr_assert_str_eq(test.getReceiver(), receiver.c_str());
}

Test(Common, CallResponse_02)
{
    const std::string sender("ugo");
    const std::string receiver("dam");
    const std::string ip("127.0.0.1");
    const std::string port("5555");

    CallResponse test(sender, receiver, ip, port);

    ASSERT_BOOL(test.encode(), true);
    ASSERT_BOOL(test.decode_header(), true);
    ASSERT_BOOL(test.decode_data_infos(), true);
    ASSERT_BOOL(test.decode_data(), true);

    cr_assert_str_eq(test.getSender(), sender.c_str());
    cr_assert_str_eq(test.getReceiver(), receiver.c_str());
    cr_assert_str_eq(test.getIp(), ip.c_str());
    cr_assert_str_eq(test.getPort(), port.c_str());

    ASSERT_BOOL(test.getDescription().empty(), false);
    ASSERT_BOOL(test.describe_code().empty(), false);
    ASSERT_BOOL(test.describe_data().empty(), false);
    ASSERT_BOOL(test.describe_data_infos().empty(), false);

}

Test(Common, CallResponse_03)
{
    const std::string sender("ugo");
    const std::string receiver("dam");
    const std::string ip("127.0.0.1");
    const std::string port("5555");
    const uint16_t call_id = 5;

    auto init = CallResponse::CallRequest(sender, receiver, ip, port);
    auto testInit = std::dynamic_pointer_cast<CallResponse>(init);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), port.c_str());
    auto serv = CallResponse::CallIncoming(std::dynamic_pointer_cast<CallResponse>(init), call_id);
    testInit = std::dynamic_pointer_cast<CallResponse>(serv);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), port.c_str());
    auto end = CallResponse::RefusedCall(std::dynamic_pointer_cast<CallResponse>(serv));

    auto test = std::dynamic_pointer_cast<CallResponse>(end);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    cr_assert_str_eq(test->getSender(), receiver.c_str());
    cr_assert_str_eq(test->getReceiver(), sender.c_str());
    cr_assert_str_eq(test->getIp(), ip.c_str());
    cr_assert_str_eq(test->getPort(), port.c_str());
}

Test(Common, CallResponse_04)
{
    const std::string sender("ugo");
    const std::string receiver("dam");
    const std::string ip("127.0.0.1");
    const std::string portStr("5555");
    const uint16_t port = 5555;
    const uint16_t call_id = 5;

    auto init = CallResponse::CallRequest(sender, receiver, ip, portStr);
    auto testInit = std::dynamic_pointer_cast<CallResponse>(init);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), portStr.c_str());

    auto serv = CallResponse::CallIncoming(std::dynamic_pointer_cast<CallResponse>(init), call_id);
    testInit = std::dynamic_pointer_cast<CallResponse>(serv);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), portStr.c_str());

    auto end = CallResponse::AcceptCall(std::dynamic_pointer_cast<CallResponse>(serv), ip, port);
    auto test = std::dynamic_pointer_cast<CallResponse>(end);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    cr_assert_str_eq(test->getSender(), receiver.c_str());
    cr_assert_str_eq(test->getReceiver(), sender.c_str());
    cr_assert_str_eq(test->getIp(), ip.c_str());
    cr_assert_str_eq(test->getPort(), portStr.c_str());
}

Test(Common, CallResponse_05)
{
    const std::string sender("ugo");
    const std::string receiver("dam");
    const std::string ip("127.0.0.1");
    const std::string port("5555");
    const uint16_t call_id = 5;

    auto init = CallResponse::CallRequest(sender, receiver, ip, port);
    auto testInit = std::dynamic_pointer_cast<CallResponse>(init);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), port.c_str());

    auto serv = CallResponse::CallIncoming(std::dynamic_pointer_cast<CallResponse>(init), call_id);
    testInit = std::dynamic_pointer_cast<CallResponse>(serv);
    ASSERT_BOOL(testInit->encode(), true);
    ASSERT_BOOL(testInit->decode_header(), true);
    ASSERT_BOOL(testInit->decode_data_infos(), true);
    ASSERT_BOOL(testInit->decode_data(), true);

    cr_assert_str_eq(testInit->getSender(), sender.c_str());
    cr_assert_str_eq(testInit->getReceiver(), receiver.c_str());
    cr_assert_str_eq(testInit->getIp(), ip.c_str());
    cr_assert_str_eq(testInit->getPort(), port.c_str());

    auto end = CallResponse::NewCallStarted(testInit->getReceiver(), testInit->getSender(), testInit->getIp(),
        testInit->getPort(), call_id);
    auto test = std::dynamic_pointer_cast<CallResponse>(end);
    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    cr_assert_str_eq(test->getSender(), receiver.c_str());
    cr_assert_str_eq(test->getReceiver(), sender.c_str());
    cr_assert_str_eq(test->getIp(), ip.c_str());
    cr_assert_str_eq(test->getPort(), port.c_str());
    ASSERT_INT(test->getCallId(), call_id);
}

Test(Common, CallResponse_sender_too_long)
{
    const std::string sender = std::string(CallResponse::MaxDataSize::Sender + 1, '*');
    const std::string receiver = std::string(CallResponse::MaxDataSize::Receiver, '*');

    cr_assert_throw(
        CallResponse test(sender, receiver),
        BabelErrors::CallResponse
    );
    try {
        CallResponse test(sender, receiver);
    } catch (const BabelErrors::CallResponse &e) {
        cr_assert_str_eq(e.what(), "sender or receiver too long");
    }
}

Test(Common, CallResponse_receiver_too_long)
{
    const std::string sender = std::string(CallResponse::MaxDataSize::Sender, '*');
    const std::string receiver = std::string(CallResponse::MaxDataSize::Receiver + 1, '*');

    cr_assert_throw(
        CallResponse test(sender, receiver),
        BabelErrors::CallResponse
    );
    try {
        CallResponse test(sender, receiver);
    } catch (const BabelErrors::CallResponse &e) {
        cr_assert_str_eq(e.what(), "sender or receiver too long");
    }
}

Test(Common, CallResponse_NewCallStarted)
{
    const std::string sender("toto");
    const std::string receiver("tata");
    const std::string ip("127.0.0.1");
    const std::string port("8080");
    uint16_t call_id = 5;
    const AResponse::ResponseType type = AResponse::ResponseType::Call;
    const CallResponse::ResponseCode code = CallResponse::ResponseCode::CallStarted;

    auto call = CallResponse::NewCallStarted(sender, receiver, ip, port, call_id);
    cr_assert_not_null(call);
    auto test = std::dynamic_pointer_cast<CallResponse>(call);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), CallResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);

    cr_assert_str_eq(test->getSender(), sender.c_str());
    cr_assert_str_eq(test->getReceiver(), receiver.c_str());
    cr_assert_str_eq(test->getIp(), ip.c_str());
    cr_assert_str_eq(test->getPort(), port.c_str());
    ASSERT_INT(test->getCallId(), call_id);
    cr_assert_neq(test->getTimestamp(), 0);
}

Test(Common, CallResponse_CallRequest)
{
    const std::string sender("toto");
    const std::string receiver("tata");
    const std::string ip("127.0.0.1");
    const std::string port("8080");
    const AResponse::ResponseType type = AResponse::ResponseType::Call;
    const CallResponse::ResponseCode code = CallResponse::ResponseCode::RequestCall;

    auto call = CallResponse::CallRequest(sender, receiver, ip, port);
    cr_assert_not_null(call);
    auto test = std::dynamic_pointer_cast<CallResponse>(call);
    cr_assert_not_null(test);

    ASSERT_BOOL(test->encode(), true);
    ASSERT_BOOL(test->decode_header(), true);
    ASSERT_BOOL(test->decode_data_infos(), true);
    ASSERT_BOOL(test->decode_data(), true);

    EXPECT_INT(test->getResponseType(), type);
    EXPECT_SIZET(test->getDataInfosSize(), CallResponse::DataInfosSize);
    EXPECT_INT(test->getCode(), code);

    cr_assert_str_eq(test->getSender(), sender.c_str());
    cr_assert_str_eq(test->getReceiver(), receiver.c_str());
    cr_assert_str_eq(test->getIp(), ip.c_str());
    cr_assert_str_eq(test->getPort(), port.c_str());
    cr_assert_eq(test->getCallId(), 0);
}
