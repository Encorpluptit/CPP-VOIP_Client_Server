###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)


###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)



###############################################################################
# Change Binary output path
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ..)
#message(${CMAKE_BINARY_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})



###############################################################################
# Set includes directories
set(
        SERVER_INCLUDES
)

include_directories(${SERVER_INCLUDE} ${BABEL_COMMON_INCLUDE})

# Includes for Tests
set(G_SERVER_INCLUDES ${SERVER_INCLUDES} PARENT_SCOPE)


###############################################################################
# Set Compile Options
add_compile_options(-Wall -Wextra -Werror)
add_definitions("-fPIC")

if (USE_LOG)
    set(USE_DEBUG ON)
    add_compile_definitions(_BABEL_LOG_)
endif (USE_LOG)

if (USE_DEBUG)
    add_compile_options(-g3)
    add_compile_definitions(_DEBUG_)
endif (USE_DEBUG)



###############################################################################
# Conan Build Management
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
#add_executable(babel main.cpp)
#target_link_libraries(babel ${CONAN_LIBS} Qt5::Widgets)



###############################################################################
# Source files
set(SERVER_SRC_DIR src)

set(
        SERVER_SOURCE_FILES

        test.cpp
        feature1/feature1.cpp
        feature2/feature2.cpp
)


foreach (src ${SERVER_SOURCE_FILES})
    set(SERVER_SOURCES ${SERVER_SOURCES} ${SERVER_SRC_DIR}/${src})
endforeach (src)


# Sources for Tests
set(G_SERVER_SOURCE ${SERVER_SOURCE} PARENT_SCOPE)


###############################################################################
# Server Executable

add_executable(
        babel_server
        main.cpp
        ${SERVER_SOURCES}
)

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
