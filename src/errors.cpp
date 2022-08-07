//
// Created by serdok on 07/08/22.
//

#include "spp-socket/errors.h"

namespace spp::errors {
    namespace {
        const SocketCategory g_category;
    }

    const std::error_category& socket_category() {
        return g_category;
    }

    const char* SocketCategory::name() const noexcept {
        return "";
    }

    std::string SocketCategory::message(int e) const {
        switch (static_cast<errc>(e)) {
        }

        throw std::invalid_argument("error code not recognized");
    }
}
