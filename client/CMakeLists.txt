###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.16)
project(CPP_babel_2020)


###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)


###############################################################################
# Set includes directories
set(
        CLIENT_INCLUDES
)

include_directories(${CLIENT_INCLUDE} ${BABEL_COMMON_INCLUDE})


###############################################################################
# Source files
set(CLIENT_SRC_DIR src)

set(
        CLIENT_SOURCE_FILES
        src/test.cpp
)


foreach (src ${SOURCE_FILES})
    set(CLIENT_SOURCE ${CLIENT_SOURCE} ${CLIENT_SRC_DIR}/${src})
endforeach (src)


add_compile_options(-Wall -Wextra -Werror)

add_executable(
        babel_client
        main.cpp
)
