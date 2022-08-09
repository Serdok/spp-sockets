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

    constexpr protocol_family make_protocol_family(int pf) { return static_cast<protocol_family>(pf); }

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

    constexpr address_format make_address_format(int af) { return static_cast<address_format>(af); }

    // List of socket types
    enum class socket_type {
        Stream          = SOCK_STREAM,
        Datagram        = SOCK_DGRAM,
    };

    constexpr socket_type make_socket_type(int st) { return static_cast<socket_type>(st); }

    // List of ip protocols
    enum class ip_protocol {
        IP              = IPPROTO_IP,
        TCP             = IPPROTO_TCP,
        UDP             = IPPROTO_UDP,
    };

    constexpr ip_protocol make_ip_protocol(int ip) { return static_cast<ip_protocol>(ip); }

    // List of socket levels
    enum class socket_level {
        IP_v4           = SOL_IP,
        Socket          = SOL_SOCKET,
    };

    constexpr socket_level make_socket_level(int sl) { return static_cast<socket_level>(sl); }

    // List of socket options
    enum class socket_option {
        DomainName      = SO_DOMAIN,
        KeepAlive       = SO_KEEPALIVE,
        Protocol        = SO_PROTOCOL,
        ReuseAddress    = SO_REUSEADDR,
        ReusePort       = SO_REUSEPORT,
        Type            = SO_TYPE,
    };

    constexpr socket_option make_socket_option(int so) { return static_cast<socket_option>(so); }

    constexpr socket_option operator bitor(socket_option o1, socket_option o2) {
        return static_cast<socket_option>(static_cast<int>(o1) bitand static_cast<int>(o2));
    }

    constexpr bool operator bitand(socket_option o1, socket_option o2) {
        return (static_cast<int>(o1) bitand static_cast<int>(o2));
    }

    struct NameInfo {
        std::string host;
        std::string port;
    };

    enum class name_info_flags {
        None                                = 0,
        // If set, then the numeric form of the host is filled
        NumericHost                        = 1,
        // If set, then the numeric form of the port is filled
        NumericPort                        = 2,
        // If set, then fail if the hostname cannot be determined
        NameRequired                       = 4,
        // If set, fill only the hostname part of the fully qualified domain name for local hosts
        NoFullyQualifiedDomainName      = 8,
        // If set, then the port is Datagram (UDP) based rather than stream (TCP) based
        Datagram                            = 16,
    };

    constexpr name_info_flags operator bitor(name_info_flags f1, name_info_flags f2) {
        return static_cast<name_info_flags>(static_cast<int>(f1) bitor static_cast<int>(f2));
    }

    constexpr bool operator bitand(name_info_flags f1, name_info_flags f2) {
        return (static_cast<int>(f1) bitand static_cast<int>(f2));
    }
}

#endif //SPP_SOCKETS_CODES_H
