//
// Created by serdok on 07/08/22.
//

#include "spp-socket/Socket.h"

#include "spp-socket/platform.h"
#include "spp-socket/utils.h"
#include <system_error>
#include <csignal>

namespace spp {
    Socket::Socket(address_format domain, socket_type type, ip_protocol protocol)
    : m_fd(socket(static_cast<int>(domain), static_cast<int>(type), static_cast<int>(protocol)))
    {
        throw_with_errno_if_error(m_fd);
    }

    Socket::~Socket() {
        close();
    }

    void Socket::close() const {
        auto ret = ::close(m_fd);
        throw_with_errno_if_error(ret);
    }

    void Socket::set_options(socket_option options, bool enabled) const {
        auto ret = setsockopt(m_fd, SOL_SOCKET, static_cast<int>(options), std::addressof(enabled), sizeof(enabled));
        throw_with_errno_if_error(ret);
    }

    void Socket::enable_options(socket_option options) const {
        set_options(options, true);
    }

    void Socket::disable_options(socket_option options) const {
        set_options(options, false);
    }

    void Socket::set_address(const SocketAddress& address) {
        m_address = address;

        sockaddr addr{};
        addr.sa_family = static_cast<int>(address.get_address_format());
        std::copy(address.get_data().begin(), address.get_data().end(), addr.sa_data);

        auto ret = bind(m_fd, &addr, sizeof(addr));
        throw_with_errno_if_error(ret);
    }
}
