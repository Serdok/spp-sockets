//
// Created by serdok on 07/08/22.
//

#include <gmock/gmock.h>
#include "spp-socket/Socket.h"
#include "spp-socket/utils.h"

TEST(SocketUnitTests, ItShouldCreateWithGivenFlags) {
    spp::Socket socket(spp::address_format::INet_v4, spp::socket_type::Stream);

    // Check that the underlying socket has detected the flags
    int fd = socket.get_underlying_fd();
    auto check_option = [fd](int opt) -> int {
        int val;
        socklen_t size = sizeof(val);
        auto ret = getsockopt(fd, SOL_SOCKET, opt, &val, &size);
        spp::throw_with_errno_if_error(ret);

        return val;
    };

    // Address format
    int opt;
    ASSERT_NO_THROW(opt = check_option(SO_DOMAIN));
    ASSERT_EQ(opt, static_cast<int>(spp::address_format::INet_v4));

    // Socket type
    ASSERT_NO_THROW(opt = check_option(SO_TYPE));
    ASSERT_EQ(opt, static_cast<int>(spp::socket_type::Stream));
}
