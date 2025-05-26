# Global
cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 20)

# Project variables
set(LOCAL_PROJECT_NAME "Stratos")
set(LOCAL_PROJECT_VERSION "1.0.0")
set(LOCAL_PROJECT_DESCRIPTION "Server software for Minecraft")

# Debugging
# For C
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")
# For C++
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")


# Source files
set(SOURCES
        Server.cpp
        network/Network.cpp
        network/Socket.cpp
        network/protocol/PacketSerialization.cpp
)

set(HEADERS
        Server.h
        network/Network.h
        network/Socket.h
        network/protocol/PacketSerialization.h
)

# Project
project(${LOCAL_PROJECT_NAME}
        VERSION ${LOCAL_PROJECT_VERSION}
        DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
        LANGUAGES CXX)

add_executable(${LOCAL_PROJECT_NAME})

list(TRANSFORM SOURCES PREPEND "src/")
list(TRANSFORM HEADERS PREPEND "src/")

target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/concurrentqueue
)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE src/Stratos.cpp ${SOURCES} ${HEADERS})

if (WIN32)
    target_link_libraries(Stratos PRIVATE iphlpapi ws2_32)
endif ()

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

# Testing
enable_testing()

add_executable("${LOCAL_PROJECT_NAME}Test" test/stratos_test.cpp)

target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/concurrentqueue
)
target_sources("${LOCAL_PROJECT_NAME}Test" PRIVATE
        ${SOURCES}
        ${HEADERS}
)

if (WIN32)
    target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE iphlpapi ws2_32)
endif()

set_target_properties("${LOCAL_PROJECT_NAME}Test" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

add_test(NAME NetworkSerialization COMMAND "${LOCAL_PROJECT_NAME}Test" --network-serialization)