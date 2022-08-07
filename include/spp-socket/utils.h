//
// Created by serdok on 07/08/22.
//

#ifndef SPP_SOCKETS_UTILS_H
#define SPP_SOCKETS_UTILS_H

#include "errors.h"

#include <array>
#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdint>
#include <cstring>


namespace spp {
    template<typename T> requires std::is_default_constructible_v<T>
    struct ErrorOr {
        T t;
        spp::errors::errc ec;
    };

    template<typename T> requires std::integral<T>
    constexpr std::array<uint8_t, sizeof(T)> convert_to_bytes_array(const T n) {
        auto array = std::array<uint8_t, sizeof(T)>();

        auto bytes = static_cast<const uint8_t*>(static_cast<const void*>(std::addressof(n)));
        std::copy(bytes, bytes + sizeof(T), array.begin());

        return array;
    }

    template<typename T> requires std::is_integral_v<T>
    constexpr T swap_byte_order(T n) {
        if constexpr (std::endian::native == std::endian::big or sizeof(T) == 1) {
            return n;
        }

        auto bytes = convert_to_bytes_array(n);
        decltype(bytes) reversed{};
        std::reverse_copy(bytes.begin(), bytes.end(), reversed.begin());

        T dest;
        std::memcpy(&dest, reversed.begin(), reversed.size());

        return dest;
    }
}

#endif //SPP_SOCKETS_UTILS_H
