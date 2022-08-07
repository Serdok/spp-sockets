//
// Created by serdok on 06/08/22.
//

#include "spp-socket/SocketAddress.h"
#include "spp-socket/utils.h"

#include <array>

namespace spp {
    void SocketAddress::set_data(std::array< uint8_t, 14 > data) {
        m_data = data;
    }
}
