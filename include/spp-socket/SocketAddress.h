//
// Created by serdok on 06/08/22.
//

#ifndef SPP_SOCKETS_SOCKETADDRESS_H
#define SPP_SOCKETS_SOCKETADDRESS_H

#include "codes.h"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>


namespace spp {
    class SocketAddress {
    public:
        /**
         * @brief Create an address to be used by sockets
         * @param format Format of the address
         * @param data Raw data of the socket
         */
        explicit constexpr SocketAddress(address_format format = address_format::Unspecified, std::array<uint8_t, 14> data = {})
                : m_format(format), m_data(data)
        {
        }

        virtual ~SocketAddress() = default;

        constexpr bool operator ==(const SocketAddress& rhs) const {
            return m_format == rhs.m_format && m_data == rhs.m_data;
        }

        [[nodiscard]] constexpr address_format get_address_format() const { return m_format; }
        constexpr void set_address_format(address_format format) { m_format = format; }
        constexpr void set_address_format(int format) { m_format = make_address_format(format); }

        [[nodiscard]] constexpr const std::array<uint8_t, 14>& get_data() const { return m_data; }
        constexpr void set_data(std::array<uint8_t, 14> data) { m_data = data; }

        [[nodiscard]] constexpr explicit operator sockaddr() const {
            sockaddr addr{};
            addr.sa_family = static_cast<int>(m_format);
            std::copy(m_data.begin(), m_data.end(), addr.sa_data);
            return addr;
        }
    protected:
        address_format m_format;
        std::array<uint8_t, 14> m_data;
    };

    // Outputs a SocketAddress using the following format:
    // "`address format`-`address byte data`"
    template<typename char_t, typename traits>
    std::basic_ostream<char_t, traits>& operator <<(std::basic_ostream<char_t, traits>& out, const SocketAddress& address) {
        typename std::basic_ostream<char_t, traits>::sentry sentry(out);
        auto stream_state = std::ios_base::goodbit;

        try {
            if (sentry) {
                // Stream ready for output
                auto format = static_cast<int>(address.get_address_format());
                auto data = address.get_data();

                out << format << '-' << data.data();
            }
        } catch (std::ios_base::failure& error) {
            stream_state |= std::ios_base::badbit;
        }

        out.setstate(stream_state);
        return out;
    }

    template<typename char_t, typename traits>
    std::basic_istream<char_t, traits>& operator >>(std::basic_istream<char_t, traits>& in, SocketAddress& address) {
        // Format: `address format`-`address byte data`
        typename std::basic_istream<char_t, traits>::sentry sentry(in);
        auto stream_state = std::ios_base::goodbit;

        try {
            if (sentry) {
                // Stream ready for input
                int format;
                std::array<uint8_t, 14> data{};

                in >> format;
                if (in.get() != '-') {
                    stream_state |= std::ios_base::failbit;
//                    throw std::ios_base::failure("expected '-' character while parsing a SocketAddress");
                }
                for (auto& c : data) {
                    in >> c;
                }

                address.set_address_format(format);
                address.set_data(data);
            }
        } catch (std::ios_base::failure& error) {
            stream_state |= std::ios_base::badbit;
        }

        in.setstate(stream_state);
        return in;
    }
}

#endif //SPP_SOCKETS_SOCKETADDRESS_H
