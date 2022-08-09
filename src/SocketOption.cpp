//
// Created by serdok on 09/08/22.
//

#include "spp-socket/SocketOption.h"

namespace spp {
    template< typename T >
    void SocketOption< T >::set_option(spp::socket_option option) {
        m_option = option;
    }
}
