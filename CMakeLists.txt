###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 17)


###############################################################################
# Compilation modes
option(USE_DEBUG "Enter debug mode" ON)
option(USE_LOG "Log Execution in a file" OFF)


###############################################################################
# Set Compile Options
add_compile_options(-Wall -Wextra)
#add_compile_options(
#        -Wshadow
#        -Wnon-virtual-dtor
#        -Wcast-align
#        -Wunused
#        -Woverloaded-virtual
#        -Wpedantic
#        -Wconversion
#        -Wduplicated-cond
#        -Wduplicated-branches
#        -Wlogical-op
#        -Wnull-dereference
#        -Wuseless-cast
#        -Wdouble-promotion
#)

if (USE_LOG)
    set(USE_DEBUG ON)
    add_compile_definitions(_BABEL_LOG_)
endif (USE_LOG)

if (USE_DEBUG)
    add_compile_options(-g3)
    add_compile_definitions(_DEBUG_)
else (USE_DEBUG)
    add_compile_options(-Werror)
endif (USE_DEBUG)


###############################################################################
# Conan Build Management
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})


###############################################################################
# Babel Common Management
set(COMMON_DIR BabelCommon)

set(
        COMMON_INCLUDES

        ${COMMON_DIR}/Utils
        ${COMMON_DIR}/Utils/Logger
        ${COMMON_DIR}/Utils/Thread
        ${COMMON_DIR}/Utils/Runnable

        ${COMMON_DIR}/Errors

        ${COMMON_DIR}/Network/NetworkInfos

        ${COMMON_DIR}/Network/Sockets/ASocket
        ${COMMON_DIR}/Network/Sockets/ClientSocket
        ${COMMON_DIR}/Network/Sockets/AsioSocket

        ${COMMON_DIR}/Network/Protocol/AResponse
        ${COMMON_DIR}/Network/Protocol/UserResponse

        ${COMMON_DIR}/Network/Protocol/CallResponse
        ${COMMON_DIR}/Network/Protocol/FriendResponse
        ${COMMON_DIR}/Network/Protocol/MessageResponse
)

set(
        COMMON_SOURCES
        ${COMMON_DIR}/Utils/Logger/Logger.cpp

        ${COMMON_DIR}/Network/NetworkInfos/NetworkInfos.cpp

        ${COMMON_DIR}/Network/Sockets/ASocket/ASocket.cpp
        ${COMMON_DIR}/Network/Sockets/AsioSocket/AsioClientSocket.cpp

        ${COMMON_DIR}/Network/Protocol/AResponse/AResponse.cpp
        ${COMMON_DIR}/Network/Protocol/UserResponse/UserResponse.cpp

        ${COMMON_DIR}/Network/Protocol/CallResponse/CallResponse.cpp
        ${COMMON_DIR}/Network/Protocol/FriendResponse/FriendResponse.cpp
        ${COMMON_DIR}/Network/Protocol/MessageResponse/MessageResponse.cpp

)

include_directories(${COMMON_INCLUDES})

###############################################################################
# Server Management
set(SERVER_DIR BabelServer)

##########################
# Server Includes
set(
        SERVER_INCLUDES
        ${SERVER_DIR}/Server
        ${SERVER_DIR}/Socket
        ${SERVER_DIR}/Listener
        ${SERVER_DIR}/Client
        ${SERVER_DIR}/AsioListener
)


##########################
# Server Sources
set(
        SERVER_SOURCES
        ${SERVER_DIR}/Server/Server.cpp
        ${SERVER_DIR}/AsioListener/AsioListener.cpp
)


##########################
# Server Executable
add_executable(
        babel_server
        ${SERVER_DIR}/main.cpp
        ${COMMON_SOURCES}
        ${SERVER_SOURCES}
)

target_include_directories(
        babel_server PUBLIC
        ${SERVER_INCLUDES}
)

target_link_libraries(babel_server ${CONAN_LIBS} stdc++fs)


###############################################################################
# Client Management
set(CLIENT_DIR BabelClient)

##########################
# Clients Includes
set(
        CLIENT_INCLUDES
        ${CLIENT_DIR}/include
        ${CLIENT_DIR}/src
)


##########################
# Client Sources
set(
        CLIENT_SOURCES
)


##########################
# Client Executable
add_executable(
        babel_client
        ${CLIENT_DIR}/main.cpp
        ${CLIENT_SOURCES}
        ${COMMON_SOURCES}
)

target_include_directories(
        babel_client PUBLIC
        ${CLIENT_INCLUDES}
)

find_package(Qt5 COMPONENTS Network REQUIRED)

target_link_libraries(babel_client ${CONAN_LIBS} stdc++fs Qt5::Widgets Qt5::Network)


###############################################################################
# Tests Configuration
set(
        TESTS_INCLUDES
        ${COMMON_INCLUDES}
        ${SERVER_INCLUDES}
        ${CMAKE_INCLUDE_PATH}
)

set(
        TESTS_SOURCES
#        tests/criterion_unit_tests/src/Common/
        tests/criterion_unit_tests/src/Common/StringFormat_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/Connection_Tests.cpp
        tests/criterion_unit_tests/src/Common/NetworkInfos_Tests.cpp
)

add_executable(
        unit_tests
        ${COMMON_SOURCES}
        ${TESTS_SOURCES}
)

target_compile_definitions(unit_tests PRIVATE _UNIT_TESTS_)

target_compile_options(unit_tests PRIVATE --coverage)

target_include_directories(unit_tests PRIVATE tests/criterion_unit_tests/include)

target_link_libraries(unit_tests criterion pthread gcov)

##########################
# Test Executable
add_executable(
        test_server
        tests/server/Chat_Message.hpp
        tests/server/Chat_Server.cpp
)
target_link_libraries(test_server pthread ${CONAN_LIBS})

add_executable(
        test_client
        tests/server/Chat_Message.hpp
        tests/server/Chat_Client.cpp
)

target_link_libraries(test_client pthread ${CONAN_LIBS})
