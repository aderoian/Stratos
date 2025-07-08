# Global
cmake_minimum_required(VERSION 3.20.0)
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
        block/state/StateProperty.cpp
        block/Blocks.cpp
        nbt/io/NBTBuffer.cpp
        nbt/CompoundTag.cpp
        nbt/ListTag.cpp
        nbt/NBT.cpp
        nbt/Value.cpp
        nbt/StringTag.cpp
        nbt/Tag.cpp
        network/Network.cpp
        network/session/NetworkClient.cpp
        network/session/SessionAuth.cpp
        network/io/Socket.cpp
        network/protocol/PacketSerialization.cpp
        network/protocol/Packet.cpp
        network/protocol/PacketCodec.cpp
        registry/Registry.cpp
        utils/collection/PalettedStorage.cpp
        utils/config/Config.cpp
        utils/crypto/CryptoUtils.cpp
        utils/hash/MD5.cpp
        utils/io/ByteBuffer.cpp
        utils/io/CompressionUtils.cpp
        utils/io/FileUtils.cpp
        utils/Identifier.cpp
        utils/StringUtils.cpp
        world/format/chunk/Chunk.cpp
        world/format/io/Region.cpp
)

set(HEADERS
        Server.h
        block/state/StateProperty.h
        block/Block.h
        block/Blocks.h
        block/BlockState.h
        math/Angle.h
        math/Ints.h
        math/Position.h
        nbt/io/NBTBuffer.h
        nbt/ArrayTag.h
        nbt/CompoundTag.h
        nbt/ListTag.h
        nbt/NBT.h
        nbt/Value.h
        nbt/PrimitiveTag.h
        nbt/StringTag.h
        nbt/Tag.h
        network/Network.h
        network/session/NetworkClient.h
        network/session/SessionAuth.h
        network/io/Socket.h
        network/protocol/PacketSerialization.h
        network/protocol/Packet.h
        network/protocol/PacketCodec.h
        registry/Registries.h
        registry/Registry.h
        utils/collection/Iterable.h
        utils/collection/PalettedStorage.h
        utils/config/Config.h
        utils/crypto/CryptoUtils.h
        utils/hash/MD5.h
        utils/io/FileUtils.h
        utils/io/ByteBuffer.h
        utils/io/CompressionUtils.h
        utils/Hash.h
        utils/Identifier.h
        utils/MathUtils.h
        utils/Predicate.h
        utils/StringUtils.h
        utils/TimeUtils.h
        utils/Types.h
        utils/UUID.h
        utils/Validate.h
        world/format/chunk/Chunk.h
        world/format/chunk/Palette.h
        world/format/io/Region.h
        world/format/Biome.h
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
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
target_sources(${LOCAL_PROJECT_NAME} PRIVATE src/Stratos.cpp ${SOURCES} ${HEADERS})

if (WIN32)
    target_link_libraries(Stratos PRIVATE iphlpapi ws2_32)
endif ()

# OpenSSL
if (WIN32)
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd")
    else()
        set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib/VC/x64/MD")
    endif()

    # Manually set the expected library paths
    set(OPENSSL_SSL_LIBRARY "${OPENSSL_LIB_DIR}/libssl.lib")
    set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_LIB_DIR}/libcrypto.lib")
    message(STATUS "Using OpenSSL from: ${OPENSSL_ROOT_DIR}\n\tInclude: ${OPENSSL_INCLUDE_DIR}\n\tSSL Library: ${OPENSSL_SSL_LIBRARY}\n\tCrypto Library: ${OPENSSL_CRYPTO_LIBRARY}")

    set(OPENSSL_USE_STATIC_LIBS TRUE)
    target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
    target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
else ()
    find_package(OpenSSL REQUIRED)
    if (OpenSSL_FOUND)
        message(STATUS "OpenSSL found: ${OPENSSL_INCLUDE_DIR} ${OpenSSL_LIBRARIES}")
        target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE ${OPENSSL_INCLUDE_DIR})
        target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE ${OPENSSL_LIBRARIES})
    else ()
        message(FATAL_ERROR "OpenSSL not found. Please install OpenSSL or set the OPENSSL_ROOT_DIR variable.")
    endif ()
endif ()

# CPR
set(CPR_USE_SYSTEM_CURL OFF)
set(CPR_BUILD_TESTS OFF)
set(CPR_ENABLE_SSL ON)
set(CPR_BUILD_TESTS OFF)
set(CURL_ZLIB OFF)
set(CURL_USE_LIBIDN2 OFF)
set(CURL_USE_LIBPSL OFF)
set(CURL_ENABLE_HTTP ON)
set(CURL_ENABLE_SSL ON)
set(BUILD_CURL_EXE OFF)
set(BUILD_SHARED_LIBS OFF)
set(CURL_STATICLIB ON)
add_subdirectory(vendor/cpr)
target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE cpr::cpr)

# Zlib
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static zlib")
add_subdirectory(vendor/zlib)
target_link_libraries(${LOCAL_PROJECT_NAME} PRIVATE zlibstatic)
target_include_directories(${LOCAL_PROJECT_NAME} PRIVATE vendor/zlib)


set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

# Testing
enable_testing()

add_executable("${LOCAL_PROJECT_NAME}Test")

target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/concurrentqueue
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/include
)
target_sources("${LOCAL_PROJECT_NAME}Test" PRIVATE
        test/stratos_test.cpp
        ${SOURCES}
        ${HEADERS}
)

if (WIN32)
    target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE iphlpapi ws2_32)
    target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE ${OPENSSL_INCLUDE_DIR})
    target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
else ()
    if (OpenSSL_FOUND)
        target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE ${OPENSSL_INCLUDE_DIR})
        target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE ${OPENSSL_LIBRARIES})
    else ()
        message(FATAL_ERROR "OpenSSL not found. Please install OpenSSL or set the OPENSSL_ROOT_DIR variable.")
    endif ()
endif()
target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE cpr::cpr)
target_link_libraries("${LOCAL_PROJECT_NAME}Test" PRIVATE zlib)
target_include_directories("${LOCAL_PROJECT_NAME}Test" PRIVATE vendor/zlib)

set_target_properties("${LOCAL_PROJECT_NAME}Test" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin")

add_test(NAME NetworkSerialization COMMAND "${LOCAL_PROJECT_NAME}Test" --network-serialization)
add_test(NAME FileUtils COMMAND "${LOCAL_PROJECT_NAME}Test" --file-utils)
add_test(NAME StringUtils COMMAND "${LOCAL_PROJECT_NAME}Test" --string-utils)
add_test(NAME ByteBuffer COMMAND "${LOCAL_PROJECT_NAME}Test" --byte-buffer)
add_test(NAME NBT COMMAND "${LOCAL_PROJECT_NAME}Test" --nbt)
add_test(NAME Palette COMMAND "${LOCAL_PROJECT_NAME}Test" --palette)
add_test(NAME Predicate COMMAND "${LOCAL_PROJECT_NAME}Test" --predicate)
