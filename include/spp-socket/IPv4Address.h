//
// Created by serdok on 06/08/22.
//

#ifndef SPP_SOCKETS_IPV4ADDRESS_H
#define SPP_SOCKETS_IPV4ADDRESS_H

#include "SocketAddress.h"
#include "utils.h"

namespace spp {
    class IPv4Address : public SocketAddress {
    public:
        /**
         * @brief Create an IPv4 socket address
         * @param address Address bytes, in host byte order
         * @param port Port number, in host byte order
         */
        explicit constexpr IPv4Address(uint32_t address = 0, uint16_t port = 0)
        : SocketAddress(address_format::INet_v4), m_host_address(address), m_host_port(port)
        {
            m_network_address = swap_byte_order(m_host_address);
            m_network_port = swap_byte_order(m_host_port);
            update_data();
        }

        [[nodiscard]] constexpr uint32_t get_host_address() const { return m_host_address; }
        [[nodiscard]] constexpr uint16_t get_host_port() const { return m_host_port; }
        [[nodiscard]] constexpr uint32_t get_network_address() const { return m_network_address; }
        [[nodiscard]] constexpr uint16_t get_network_port() const { return m_network_port; }

        constexpr void set_host_address(uint32_t address) {
            m_host_address = address;
            m_network_address = swap_byte_order(m_host_address);
            update_data();
        }

        constexpr void set_host_port(uint16_t port) {
            m_host_port = port;
            m_network_port = swap_byte_order(m_host_port);
            update_data();
        }

        [[nodiscard]] std::string address_to_string() const;
        [[nodiscard]] std::string port_to_string() const;
        [[nodiscard]] std::string to_string() const;

    private:
        constexpr void update_data() {
            // In the C struct sockaddr_in, the port is assigned before the address.
            // Therefore, when casting a sockaddr_in* to a sockaddr*,
            // the sockaddr.sa_data is filled with the bytes of the port number, then the network address

            auto port_bytes = convert_to_bytes_array(m_network_port);
            auto address_bytes = convert_to_bytes_array(m_network_address);

            auto it = m_data.begin();
            it = std::copy(port_bytes.begin(), port_bytes.end(), it);
            std::copy(address_bytes.begin(), address_bytes.end(), it);
        }

    private:
        uint32_t m_host_address;
        uint16_t m_host_port;
        uint32_t m_network_address;
        uint16_t m_network_port;
    };
}

#endif //SPP_SOCKETS_IPV4ADDRESS_H
