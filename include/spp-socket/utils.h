//
// Created by serdok on 07/08/22.
//

#ifndef SPP_SOCKETS_UTILS_H
#define SPP_SOCKETS_UTILS_H

#include <array>
#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdint>
#include <cstring>


namespace spp {
    template<typename T> requires std::integral<T>
    constexpr std::array<uint8_t, sizeof(T)> convert_to_bytes_array(const T n) {
        auto array = std::array<uint8_t, sizeof(T)>();

        auto bytes = static_cast<const uint8_t*>(static_cast<const void*>(std::addressof(n)));
        std::copy(bytes, bytes + sizeof(T), array.begin());

        return array;
    }

    template<typename T> requires std::is_integral_v<T>
    constexpr T swap_byte_order(T n) {
        if constexpr (std::endian::native == std::endian::big or sizeof(T) == 1) {  // NOLINT
            return n;
        }

        auto bytes = convert_to_bytes_array(n);
        decltype(bytes) reversed{};
        std::reverse_copy(bytes.begin(), bytes.end(), reversed.begin());

        T dest;
        std::memcpy(&dest, reversed.begin(), reversed.size());

        return dest;
    }

    inline void throw_with_errno_if_error(int code) {
        if (code < 0) {
            auto ec = std::make_error_code(static_cast<std::errc>(errno));
            throw std::system_error(ec);
        }
    }
}

#endif //SPP_SOCKETS_UTILS_H
