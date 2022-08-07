# Init and update submodules if necessary
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/modules" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.gitmodules")
    return ()
endif()

find_program(GIT git)
if (GIT-NOTFOUND)
    return ()
endif()

execute_process(
        COMMAND ${GIT} submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_RESULT
)
if (NOT ${GIT_RESULT} EQUAL 0)
    message(FATAL_ERROR "Initializing git submodules failed with error code ${GIT_RESULT}.")
endif()