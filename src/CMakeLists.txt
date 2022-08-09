# Set library sources
target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
            "${PROJECT_SOURCE_DIR}/src"
        PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_sources(
        ${PROJECT_NAME}
        PRIVATE SocketAddress.cpp IPv4Address.cpp errors.cpp Socket.cpp
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE
            $<$<PLATFORM_ID:Windows>:SPP_PLATFORM_IS_WINDOWS>
            $<$<STREQUAL:CMAKE_CXX_BYTE_ORDER,BIG_ENDIAN>:SPP_BIG_ENDIAN>
)

target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
            -Werror
)

# Link external libraries
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE fmt
)

# Set target properties
set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED TRUE
        VERSION ${PROJECT_VERSION}
)
