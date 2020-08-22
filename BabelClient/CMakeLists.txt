###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)


###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)



###############################################################################
# Set includes directories
set(
        CLIENT_INCLUDES
        SaveQT
)

include_directories(${CLIENT_INCLUDES} ${BABEL_COMMON_INCLUDE})



###############################################################################
# Set Compile Options
add_compile_options(-Wall -Wextra)
add_definitions("-fPIC")

if (USE_LOG)
    set(USE_DEBUG ON)
    add_compile_definitions(_BABEL_LOG_)
endif (USE_LOG)

if (USE_DEBUG)
    add_compile_options(-g3)
    add_compile_definitions(_DEBUG_)
else(USE_DEBUG)
    add_compile_options(-Werror)
endif (USE_DEBUG)



###############################################################################
# Conan Build Management
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})



###############################################################################
# Source files
set(CLIENT_SRC_DIR src)

set(
        CLIENT_SOURCE_FILES

        SaveQT/test.cpp
)


foreach (src ${CLIENT_SOURCE_FILES})
    set(CLIENT_SOURCES ${CLIENT_SOURCES} ${CLIENT_SRC_DIR}/${src})
endforeach (src)


# Sources for Tests
# set(G_CLIENT_SOURCE ${CLIENT_SOURCE} PARENT_SCOPE)

# Includes for Tests
# set(G_SERVER_INCLUDES ${SERVER_INCLUDES} PARENT_SCOPE)



###############################################################################
# Change Binary output path
#set(EXECUTABLE_OUTPUT_PATH ..)



###############################################################################
# Client executable

add_executable(
        babel_client
        SaveQT/test.cpp
)

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
