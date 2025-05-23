# Global
cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)

# Project variables
set(LOCAL_PROJECT_NAME "Stratos")
set(LOCAL_PROJECT_VERSION "1.0.0")
set(LOCAL_PROJECT_DESCRIPTION "Server software for Minecraft")

# Source files
set(SOURCES
        Stratos.cpp
        Server.cpp
        network/Network.cpp
        network/Socket.cpp
)

set(HEADERS
        Server.h
        network/Network.h
        network/Socket.h
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
target_sources(${LOCAL_PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})

if (WIN32)
    target_link_libraries(Stratos PRIVATE iphlpapi ws2_32)
endif ()

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")