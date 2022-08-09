cmake_minimum_required(VERSION 3.20)
project(
        spp_sockets
        VERSION 0.0.1
        LANGUAGES CXX
)

# Set options
option(ENABLE_TESTING "Configure CMake to add tests" OFF)
option(BUILD_SHARED_LIBS "Configure CMake to build a shared library instead of a static one" OFF)

# Set global parameters
list(PREPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
set(namespace "spp")
set(CMAKE_CXX_STANDARD 20)

# Include project scripts
add_subdirectory(scripts/)
include(check-submodules)

# Include third-party projects
add_subdirectory(vendor/)

# Add library and sources
add_library(${PROJECT_NAME})
add_library(${namespace}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_subdirectory(src/)

# Enable testing if requested or the current project is the top-level one
if (ENABLE_TESTING OR (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME))
    add_subdirectory(tests/)
endif()

add_executable(sandbox sandbox.cpp)
target_link_libraries(sandbox PRIVATE ${PROJECT_NAME})
