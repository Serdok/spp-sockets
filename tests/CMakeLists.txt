# Testing configurations
enable_testing()
include(GoogleTest)

function(create_unit_test module_name)
    # Create executable
    add_executable(${module_name}_unit_tests)
    target_sources(${module_name}_unit_tests PRIVATE ${module_name}_unit_tests.cpp)
    target_link_libraries(${module_name}_unit_tests PRIVATE ${PROJECT_NAME} gmock gmock_main)

    # Discover tests
    gtest_discover_tests(ipv4_address_unit_tests)
endfunction()

# Unit tests
create_unit_test(ipv4_address)
create_unit_test(socket)
