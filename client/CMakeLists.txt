###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)

set(EXECUTABLE_OUTPUT_PATH ..)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

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
# Set Compile Options
add_compile_options(-Wall -Wextra -Werror)

if (USE_LOG)
    set(USE_DEBUG ON)
    add_compile_definitions(_BABEL_LOG_)
endif (USE_LOG)

if (USE_DEBUG)
    add_compile_options(-g3)
    add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)

###############################################################################
# Source files
set(CLIENT_SRC_DIR src)

set(
        CLIENT_SOURCE_FILES

        test.cpp
        feature1/feature1.cpp
        feature2/feature2.cpp
)


foreach (src ${CLIENT_SOURCE_FILES})
    set(CLIENT_SOURCES ${CLIENT_SOURCES} ${CLIENT_SRC_DIR}/${src})
endforeach (src)

###############################################################################
# Client executable

add_executable(
        babel_client
        main.cpp
        ${CLIENT_SOURCES}
)
