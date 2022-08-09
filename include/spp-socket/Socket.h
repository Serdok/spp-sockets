//
// Created by serdok on 07/08/22.
//

#ifndef SPP_SOCKETS_SOCKET_H
#define SPP_SOCKETS_SOCKET_H

#include "codes.h"
#include "SocketAddress.h"

namespace spp {
    class Socket {
    public:
        Socket(address_format domain, socket_type type, ip_protocol protocol = ip_protocol::IP);

        virtual ~Socket();
        void close() const;

        void set_options(socket_option options, bool enabled) const;
        void enable_options(socket_option options) const;
        void disable_options(socket_option options) const;

        void set_address(const SocketAddress& address);
        [[nodiscard]] constexpr const SocketAddress& get_address() const {
            return m_address;
        }

        [[nodiscard]] constexpr int get_underlying_fd() const {
            return m_fd;
        }

    private:
        int m_fd;
        SocketAddress m_address;
    };
}

#endif //SPP_SOCKETS_SOCKET_H
