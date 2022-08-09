//
// Created by serdok on 06/08/22.
//

#include "spp-socket/IPv4Address.h"

#include <sstream>
#include <fmt/format.h>

namespace spp {
    std::string IPv4Address::address_to_string() const {
        std::ostringstream ss{};

        auto bytes = convert_to_bytes_array(m_host_address);

        return fmt::format("{}.{}.{}.{}", bytes.at(3), bytes.at(2), bytes.at(1), bytes.at(0));
    }

    std::string IPv4Address::port_to_string() const {
        return std::to_string(m_host_port);
    }

    std::string IPv4Address::to_string() const {
        return fmt::format("{}:{}", address_to_string(), port_to_string());
    }
}
