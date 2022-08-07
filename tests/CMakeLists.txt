# Testing configurations
enable_testing()
include(GoogleTest)


# Executables
add_executable(ipv4_address_unit_tests)
target_sources(ipv4_address_unit_tests PRIVATE ipv4_address_unit_tests.cpp)
target_link_libraries(ipv4_address_unit_tests PRIVATE ${PROJECT_NAME} gmock gmock_main)


# Discover tests in above executables
gtest_discover_tests(ipv4_address_unit_tests)
