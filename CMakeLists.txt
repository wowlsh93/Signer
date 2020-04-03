cmake_minimum_required(VERSION 3.10)
project(Signer)

set(CMAKE_CXX_STANDARD 17)

find_library(
        LIBSODIUM
        NAMES libsodium.so
        HINTS /usr/lib /usr/lib64
        REQUIRED)

add_executable(Signer main.cpp crypto/signer.cpp crypto/signer.h command/command.cpp command/command.h util/util.h crypto/ed25519.cpp crypto/ed25519.h crypto/secp256k1.cpp crypto/secp256k1.h test.h util/crc16.cpp util/crc16.h util/base32.cpp util/base32.h util/stella_format.cpp util/stella_format.h)

target_link_libraries(${PROJECT_NAME} ${LIBSODIUM})