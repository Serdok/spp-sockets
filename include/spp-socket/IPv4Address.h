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

        [[nodiscard]] constexpr explicit operator sockaddr_in() const {
            sockaddr_in addr{};
            addr.sin_family = static_cast<int>(m_format);
            addr.sin_addr.s_addr = m_network_address;
            addr.sin_port = m_network_port;
            return addr;
        }

    private:
        constexpr void update_data() {
            // In the C struct sockaddr_in, the port is assigned before the address.
            // Therefore, when casting a sockaddr_in* to a sockaddr*,
            // the sockaddr.sa_data is filled with the bytes of the network port number, then the network address

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

    // Outputs a SocketAddress using the following format:
    // "`address format`-`address IP address`:`address port number`"
    template<typename char_t, typename traits>
    std::basic_ostream<char_t, traits>& operator <<(std::basic_ostream<char_t, traits>& out, const IPv4Address& address)  {
        typename std::basic_ostream<char_t, traits>::sentry sentry(out);
        auto stream_state = std::ios_base::goodbit;

        try {
            if (sentry) {
                // Stream ready for output
                out << address.to_string();
            }
        } catch (std::ios_base::failure& error) {
            stream_state |= std::ios_base::badbit;
        }

        out.setstate(stream_state);
        return out;
    }

    template<typename char_t, typename traits>
    std::basic_istream<char_t, traits>& operator >>(std::basic_istream<char_t, traits>& in, IPv4Address& address) {
        // Format: `address format`-`address IP address`:`address port number`
        typename std::basic_istream<char_t, traits>::sentry sentry(in);
        auto stream_state = std::ios_base::goodbit;

        auto read_ip_byte = [&](int shift_pos, bool check_next = true) {
            int byte = 0;
            in >> byte;
            if (check_next and in.get() != '.') {
                stream_state |= std::ios_base::failbit;
//                throw std::ios_base::failure("expected '.' character while parsing an IPv4Address");
            }

            return byte << (8 * shift_pos);
        };

        try {
            if (sentry) {
                // Stream ready for input
                uint32_t ip_address = 0;
                uint16_t port = 0;

                auto byte1 = read_ip_byte(3);
                auto byte2 = read_ip_byte(2);
                auto byte3 = read_ip_byte(1);
                auto byte4 = read_ip_byte(0, false);
                ip_address = byte1 bitor byte2 bitor byte3 bitor byte4;

                if (in.get() != ':') {
                    stream_state |= std::ios_base::failbit;
//                    throw std::ios_base::failure("expected ':' character while parsing an IPv4Address");
                }
                in >> port;

                address.set_address_format(spp::address_format::INet_v4);
                address.set_host_address(ip_address);
                address.set_host_port(port);
            }
        } catch (std::ios_base::failure& error) {
            stream_state |= std::ios_base::badbit;
        }

        in.setstate(stream_state);
        return in;
    }
}

#endif //SPP_SOCKETS_IPV4ADDRESS_H
