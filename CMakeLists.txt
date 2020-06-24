###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)

#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

#set(BIN_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(BIN_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} CACHE INTERNAL lol)
#message(${CMAKE_CURRENT_BINARY_DIR})



###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)


###############################################################################
# Compilation Options
option(USE_DEBUG "Enter debug mode" OFF)
option(USE_LOG "Log Execution in a file" OFF)

#if (USE_DEBUG)
#    add_compile_options(-g3)
#    add_compile_definitions(_DEBUG_)
#endif (USE_DEBUG)
#
#if (USE_LOG)
#    set(USE_DEBUG ON)
#    add_compile_definitions(_BABEL_LOG_)
#endif (USE_LOG)


###############################################################################
# Common includes
set(
        BABEL_COMMON_INCLUDE
        ${PROJECT_SOURCE_DIR}/common
)


###############################################################################
# Subdirectories Configuration
add_subdirectory(client)
add_subdirectory(server)
