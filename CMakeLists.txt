###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)


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
add_definitions("-fPIC")

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
        ${COMMON_DIR}/Logger

        ${COMMON_DIR}/Debug

        ${COMMON_DIR}/StringFormat

        ${COMMON_DIR}/Protocol/IResponse
        ${COMMON_DIR}/Protocol/AResponse
        ${COMMON_DIR}/Protocol/Connection

        ${COMMON_DIR}/Network/NetworkInfos

        ${COMMON_DIR}/Network/Sockets/ISocket
        ${COMMON_DIR}/Network/Sockets/ASocket
#        ${COMMON_DIR}/Network/Sockets/TcpSocket

        ${COMMON_DIR}/Thread/AThread
        ${COMMON_DIR}/Thread/BoostThread

)

set(
        COMMON_SOURCES
        ${COMMON_DIR}/Logger/Logger.cpp
        ${COMMON_DIR}/Logger/LoggerError.cpp

        ${COMMON_DIR}/Protocol/IResponse/IResponse.cpp
        ${COMMON_DIR}/Protocol/AResponse/AResponse.cpp
        ${COMMON_DIR}/Protocol/Connection/ConnectionResponse.cpp

        ${COMMON_DIR}/Network/NetworkInfos/NetworkInfos.cpp

        ${COMMON_DIR}/Network/Sockets/ISocket/ISocket.cpp
        ${COMMON_DIR}/Network/Sockets/ASocket/ASocket.cpp

        ${COMMON_DIR}/Thread/AThread/AThread.cpp
        ${COMMON_DIR}/Thread/BoostThread/BoostThread.cpp

        #        ${COMMON_DIR}/Network/Sockets/TcpSocket/TcpSocket.cpp
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
)


##########################
# Server Sources
set(
        SERVER_SOURCES
        ${SERVER_DIR}/test.cpp
        ${SERVER_DIR}/Server/Server.cpp
        ${SERVER_DIR}/Socket/Socket.cpp
)


##########################
# Server Executable
add_executable(
        babel_server
        ${SERVER_DIR}/main.cpp
        ${SERVER_SOURCES}
        ${COMMON_SOURCES}
)

target_include_directories(
        babel_server PUBLIC
        ${SERVER_INCLUDES}
)

target_link_libraries(babel_server ${CONAN_LIBS})


###############################################################################
# Client Management
set(CLIENT_DIR BabelClient)

##########################
# Clients Includes
set(
        CLIENT_INCLUDES
        ${CLIENT_DIR}/include
)


##########################
# Client Sources
set(
        CLIENT_SOURCES
        ${CLIENT_DIR}/src/feature1/feature1.cpp
        ${CLIENT_DIR}/src/feature2/feature2.cpp
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

target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)


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
        tests/criterion_unit_tests/src/Common/Protocol_Tests.cpp
        tests/criterion_unit_tests/src/Common/NetworkInfos_Tests.cpp
)

add_executable(
        unit_tests
        ${COMMON_SOURCES}
        ${TESTS_SOURCES}
)

target_compile_definitions(unit_tests PRIVATE _UNIT_TESTS_)


target_include_directories(unit_tests PRIVATE tests/criterion_unit_tests/include)

target_link_libraries(unit_tests criterion pthread)

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
#target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets)
