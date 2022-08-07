//
// Created by serdok on 06/08/22.
//

#ifndef SPP_SOCKETS_SOCKETADDRESS_H
#define SPP_SOCKETS_SOCKETADDRESS_H

#include "codes.h"
#include "utils.h"

#include <array>
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

        [[nodiscard]] constexpr const std::array<uint8_t, 14>& get_data() const { return m_data; }
        void set_data(std::array<uint8_t, 14> data);

    protected:
        address_format m_format;
        std::array<uint8_t, 14> m_data;
    };
}

#endif //SPP_SOCKETS_SOCKETADDRESS_H
