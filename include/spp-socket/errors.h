//
// Created by serdok on 07/08/22.
//

#ifndef SPP_SOCKETS_ERRORS_H
#define SPP_SOCKETS_ERRORS_H

#include "platform.h"
#include <system_error>

namespace spp::errors {
    enum class errc {
//        unresolved_name = EAI_NONAME,
    };

    class SocketCategory : public std::error_category {
    public:
        ~SocketCategory() override = default;

        [[nodiscard]] const char* name() const noexcept override;
        [[nodiscard]] std::string message(int e) const override;
    };

    const std::error_category& socket_category();

    static std::error_condition make_error_condition(errc e) noexcept {
        return {static_cast<int>(e), spp::errors::socket_category()};
    }
    static std::error_code make_error_code(errc e) noexcept {
        return {static_cast<int>(e), spp::errors::socket_category()};
    }
}

// Extend <system_error> error codes
template<>
struct std::is_error_condition_enum< spp::errors::errc > : true_type {};

#endif //SPP_SOCKETS_ERRORS_H
