//
// Created by serdok on 06/08/22.
//

#ifndef SPP_SOCKETS_CODES_H
#define SPP_SOCKETS_CODES_H

#include "platform.h"

#include <string>

namespace spp {
    // List of protocol families
    enum class protocol_family {
        Unspecified     = PF_UNSPEC,
        Local           = PF_LOCAL,
        Unix            = PF_UNIX,
        File            = PF_FILE,
        INet_v4         = PF_INET,
        INet_v6         = PF_INET6,
        Bluetooth       = PF_BLUETOOTH,
    };

    // List of address formats
    enum class address_format {
        Unspecified     = AF_UNSPEC,
        Local           = AF_LOCAL,
        Unix            = AF_UNIX,
        File            = AF_FILE,
        INet_v4         = AF_INET,
        INet_v6         = AF_INET6,
        Bluetooth       = AF_BLUETOOTH,
    };

    constexpr sa_family_t to_sa_family_t(address_format format) {
        return static_cast<sa_family_t>(format);
    }

    struct NameInfo {
        std::string host;
        std::string port;
    };

    enum class name_info_flags {
        none                                = 0,
        // If set, then the numeric form of the host is filled
        numeric_host                        = 1,
        // If set, then the numeric form of the port is filled
        numeric_port                        = 2,
        // If set, then fail if the hostname cannot be determined
        name_required                       = 4,
        // If set, fill only the hostname part of the fully qualified domain name for local hosts
        no_fully_qualified_domain_name      = 8,
        // If set, then the port is datagram (UDP) based rather than stream (TCP) based
        datagram                            = 16,
    };

    constexpr name_info_flags operator bitor(name_info_flags f1, name_info_flags f2) {
        return static_cast<name_info_flags>(static_cast<int>(f1) bitor static_cast<int>(f2));
    }

    constexpr bool operator bitand(name_info_flags f1, name_info_flags f2) {
        return (static_cast<int>(f1) bitand static_cast<int>(f2));
    }
}

#endif //SPP_SOCKETS_CODES_H
