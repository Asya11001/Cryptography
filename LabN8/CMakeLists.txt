cmake_minimum_required(VERSION 3.25)
project(LabN8 C)

set(CMAKE_C_STANDARD 11)

find_package(OpenSSL REQUIRED)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

# Add executable and link against OpenSSL library
add_executable(LabN8 main.c)
target_link_libraries(LabN8 ${OPENSSL_LIBRARIES})
