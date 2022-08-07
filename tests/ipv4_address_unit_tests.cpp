//
// Created by serdok on 07/08/22.
//

#include <gmock/gmock.h>
#include <spp-socket/IPv4Address.h>


TEST(IPv4AddressUnitTests, ItShouldDefaultToZero) {
    spp::IPv4Address address;

    ASSERT_EQ(address.to_string(), "0.0.0.0:0");
}



