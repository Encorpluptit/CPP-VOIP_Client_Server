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

//Test(Common, UserResponse_14)
//{
//    const std::string login = std::string(UserResponse::MaxDataSize::Login + 1, '*');
//    const std::string pass = std::string(UserResponse::MaxDataSize::Password, '*');
//
//    cr_assert_throw(
//        UserResponse test(login, pass),
//        BabelErrors::UserResponse
//    );
//    try {
//        UserResponse test(login, pass);
//    } catch (const BabelErrors::UserResponse &e) {
//        cr_assert_str_eq(e.what(), "login or password too long");
//    }
//}
