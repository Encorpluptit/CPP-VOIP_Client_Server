###############################################################################
# Project Configuration
cmake_minimum_required(VERSION 3.14)
project(CPP_babel_2020)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

###############################################################################
# Language Configuration
set(CMAKE_CXX_STANDARD 20)


###############################################################################
# Compilation modes
option(USE_DEBUG "Enter debug mode" ON)
option(USE_LOG "Log Execution in a file" OFF)
option(GH_TESTS "Github tests for disable port audio" OFF)


###############################################################################
# Set Compile Options
if (UNIX)
    add_compile_options(-Wall -Wextra)
endif (UNIX)

if (USE_LOG)
    set(USE_DEBUG ON)
    add_compile_definitions(_BABEL_LOG_)
endif (USE_LOG)

if (COVERAGE)
    add_compile_options(--coverage -fprofile-arcs -ftest-coverage)
endif (COVERAGE)

if (USE_DEBUG)
    if (UNIX)
        add_compile_options(-g3)
    endif (UNIX)
    add_compile_definitions(_DEBUG_)
else (USE_DEBUG)
    if (UNIX)
        add_compile_options(-Werror)
    endif (UNIX)
endif (USE_DEBUG)


###############################################################################
# Conan Build Management
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CMAKE_INCLUDE_PATH})

find_package(Qt5Widgets CONFIG REQUIRED)

set(BOOST_DEBUG ON)
if (UNIX)
    find_package(Boost COMPONENTS thread REQUIRED)
    if (BOOST_FOUND)
        set(CONAN_LIBS ${CONAN_LIBS} Boost::thread)
    endif (BOOST_FOUND)
else (UNIX)
    find_package(Boost REQUIRED)
    if (Boost_FOUND)
        set(CONAN_LIBS ${CONAN_LIBS} libboost_thread)
    endif (Boost_FOUND)
endif (UNIX)


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

        ${COMMON_DIR}/Database

        ${COMMON_DIR}/Network/NetworkInfos

        ${COMMON_DIR}/Network/Sockets/ASocket
        ${COMMON_DIR}/Network/Sockets/ClientSocket

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

        ${COMMON_DIR}/Network/Protocol/AResponse/AResponse.cpp

        ${COMMON_DIR}/Network/Protocol/UserResponse/UserResponse.cpp
        ${COMMON_DIR}/Network/Protocol/UserResponse/FormattedUserResponse.cpp

        ${COMMON_DIR}/Network/Protocol/CallResponse/CallResponse.cpp
        ${COMMON_DIR}/Network/Protocol/CallResponse/FormattedCallResponse.cpp

        ${COMMON_DIR}/Network/Protocol/FriendResponse/FriendResponse.cpp
        ${COMMON_DIR}/Network/Protocol/FriendResponse/FormattedFriendResponse.cpp

        ${COMMON_DIR}/Network/Protocol/MessageResponse/MessageResponse.cpp
        ${COMMON_DIR}/Network/Protocol/MessageResponse/FormattedMessageResponse.cpp

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
        ${SERVER_DIR}/Sockets/
        ${SERVER_DIR}/Sockets/Listener
        ${SERVER_DIR}/Sockets/Listener/AsioListener
        ${SERVER_DIR}/Sockets/AsioSocket
        ${SERVER_DIR}/Database
        ${SERVER_DIR}/RequestManager
        ${SERVER_DIR}/RequestManager/UserManager
        ${SERVER_DIR}/RequestManager/CallManager
        ${SERVER_DIR}/RequestManager/FriendManager
        ${SERVER_DIR}/RequestManager/MessageManager
)


##########################
# Server Sources
set(
        SERVER_SOURCES
        ${SERVER_DIR}/Server/Server.cpp
        ${SERVER_DIR}/Sockets/AsioSocket/AsioClientSocket.cpp
        ${SERVER_DIR}/Sockets/Listener/AsioListener/AsioListener.cpp
        ${SERVER_DIR}/Database/Database.cpp
        ${SERVER_DIR}/RequestManager/RequestManager.cpp
        ${SERVER_DIR}/RequestManager/UserManager/UserManager.cpp
        ${SERVER_DIR}/RequestManager/CallManager/CallManager.cpp
        ${SERVER_DIR}/RequestManager/FriendManager/FriendManager.cpp
        ${SERVER_DIR}/RequestManager/MessageManager/MessageManager.cpp
)


##########################
# Server Executable
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
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
# TODO: REMOVE WHEN FIX SQLITE_ORM.
if (UNIX)
    target_compile_options(babel_server PRIVATE -Wno-redundant-move)
    target_link_libraries(babel_server stdc++fs)
endif (UNIX)

target_link_libraries(babel_server ${CONAN_LIBS})


###############################################################################
# Client Management
set(CLIENT_DIR BabelClient)

##########################
# Clients Includes
set(
        CLIENT_INCLUDES
        ${CLIENT_DIR}/ClientCore
)


##########################
# Client Sources
set(
        CLIENT_SOURCES
        ${CLIENT_DIR}/ClientCore/ClientCore.cpp
        ${CLIENT_DIR}/ClientCore/mainwindow.cpp
        ${CLIENT_DIR}/ClientCore/QtSocket.cpp
        ${CLIENT_DIR}/ClientCore/QUdpSocket.cpp
        ${CLIENT_DIR}/ClientCore/Opus.cpp
        ${CLIENT_DIR}/ClientCore/PortAudio.cpp
)


##########################
# Client Executable
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
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

target_compile_definitions(babel_client PRIVATE BABEL_CLIENT_BIN)

find_package(Qt5 COMPONENTS Network Widgets REQUIRED)
<<<<<<< HEAD
#target_link_libraries(babel_client ${CONAN_LIBS} stdc++fs Qt5::Widgets Qt5::Network)
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network)
#target_link_libraries(babel_client ${CONAN_LIBS} stdc++fs)
if (UNIX)
target_link_libraries(babel_server stdc++fs)
endif (UNIX)
=======
target_link_libraries(babel_client ${CONAN_LIBS} stdc++fs Qt5::Widgets Qt5::Network)
>>>>>>> server


###############################################################################
# Tests Configuration
if (UNIX)
set(
TESTS_INCLUDES
${COMMON_INCLUDES}
${SERVER_INCLUDES}
${CLIENT_INCLUDES}
        ${CMAKE_INCLUDE_PATH}
)

set(
        TESTS_SOURCES
        tests/criterion_unit_tests/src/Common/StringFormat_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/UserRequest_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/CallRequest_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/FriendRequest_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/MessageRequest_Tests.cpp
        tests/criterion_unit_tests/src/Common/Protocol/ARequest_Tests.cpp
        tests/criterion_unit_tests/src/Common/NetworkInfos_Tests.cpp
        tests/criterion_unit_tests/src/Client/Client.cpp
        ${CLIENT_DIR}/ClientCore/Opus.cpp
        ${CLIENT_DIR}/ClientCore/PortAudio.cpp
)

add_executable(
        unit_tests
        ${COMMON_SOURCES}
        ${TESTS_SOURCES}
)

target_compile_definitions(unit_tests PRIVATE _UNIT_TESTS_)

target_compile_options(unit_tests PRIVATE --coverage)

target_include_directories(unit_tests PRIVATE tests/criterion_unit_tests/include
${CLIENT_INCLUDES})

target_link_libraries(unit_tests criterion ${CONAN_LIBS} gcov stdc++fs Qt5::Widgets Qt5::Network)

set_target_properties(unit_tests PROPERTIES CXX_STANDARD 17)
<<<<<<< HEAD
endif (UNIX)
=======

if (GH_TESTS)
target_compile_definitions(unit_tests PRIVATE GH_TESTS)
endif (GH_TESTS)
>>>>>>> server
