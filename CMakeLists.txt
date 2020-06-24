###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)



###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)


###############################################################################
# Compilation Options
option(USE_DEBUG "Enter debug mode" OFF)
option(USE_LOG "Log Execution in a file" OFF)


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



###############################################################################
# Tests Configuration

