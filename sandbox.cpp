//
// Created by serdok on 08/08/22.
//

#include <spp-socket/SocketAddress.h>
#include <spp-socket/IPv4Address.h>
#include <spp-socket/utils.h>

#include <sstream>

int main() {
    uint32_t address = 0xc0a80f01;  // 192.168.15.1 = 3232304897
    uint16_t port = 0x1f90;         // 8080
    std::istringstream data_ss("2-\x1f\x90\xc0\xa8\x0f\x01");
    std::istringstream ip_ss("192.168.15.1:8080");

    auto address_bytes = spp::convert_to_bytes_array(address);
    auto port_bytes = spp::convert_to_bytes_array(port);

    std::array<uint8_t, 14> data{};
    auto it = data.begin();
    it = std::copy(port_bytes.begin(), port_bytes.end(), it);
    std::copy(address_bytes.begin(), address_bytes.end(), it);

    {
        spp::IPv4Address addr(address, port);
        std::cout << addr << std::endl;
        std::cout << *dynamic_cast<spp::SocketAddress*>(&addr) << std::endl;

        spp::IPv4Address addr2;
        ip_ss >> addr2;
        std::cout << addr2 << std::endl;
        std::cout << *dynamic_cast<spp::SocketAddress*>(&addr2) << std::endl;

        std::cout << std::boolalpha << (addr == addr2) << std::endl;
    }
    std::cout << std::endl;
    {
        spp::IPv4Address addr(address, port);
        std::cout << addr << std::endl;
        std::cout << *dynamic_cast<spp::SocketAddress*>(&addr) << std::endl;

        spp::SocketAddress addr2;
        data_ss >> addr2;
        std::cout << addr2 << std::endl;

        auto sock = static_cast<sockaddr>(addr);
        auto sock2 = static_cast<sockaddr>(addr2);

        std::cout << std::boolalpha << (sock.sa_family == sock2.sa_family) << std::endl;
    }

    return 0;
}
