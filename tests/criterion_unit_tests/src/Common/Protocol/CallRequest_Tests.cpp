#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-pro-type-member-init"
#pragma ide diagnostic ignored "cert-err58-cpp"
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
