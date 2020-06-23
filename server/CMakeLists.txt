###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)


###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)

###############################################################################
# Set includes directories
set(
        SERVER_INCLUDES
)


include_directories(${SERVER_INCLUDE} ${BABEL_COMMON_INCLUDE})


###############################################################################
# Source files
set(CLIENT_SRC_DIR src)

set(
        CLIENT_SOURCE_FILES

        src/test.cpp
        feature1/feature1.cpp
        feature2/feature2.cpp
)

add_compile_options(-Wall -Wextra -Werror)

add_executable(
        babel_server
        main.cpp
)
