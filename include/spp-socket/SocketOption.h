//
// Created by serdok on 08/08/22.
//

#ifndef SPP_SOCKETS_SOCKETOPTION_H
#define SPP_SOCKETS_SOCKETOPTION_H

#include "codes.h"
#include <tuple>

namespace spp {
    template<typename T>
    class SocketOption {
    public:


    private:
        T m_value;
        unsigned int m_value_size;
    };


}

#endif //SPP_SOCKETS_SOCKETOPTION_H
