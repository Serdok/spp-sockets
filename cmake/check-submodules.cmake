# Init and update submodules if necessary
message(VERBOSE "Checking if we need to initialize git submodules...")
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/modules" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.gitmodules")
    message(VERBOSE "No git submodules found.")
    return ()
endif()

find_program(GIT git)
if (GIT-NOTFOUND)
    message(VERBOSE "`git` executable not found.")
    return ()
endif()

message(VERBOSE "Initializing git submodules")
execute_process(
        COMMAND ${GIT} submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_RESULT
)
if (NOT ${GIT_RESULT} EQUAL 0)
    message(FATAL_ERROR "Initializing git submodules failed with error code ${GIT_RESULT}.")
endif()

message(VERBOSE "Done.")