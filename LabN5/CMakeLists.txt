cmake_minimum_required(VERSION 3.25)
project(LabN5 C)

set(CMAKE_C_STANDARD 11)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(LabN5 main.c)

target_link_libraries(LabN5 ${OPENSSL_LIBRARIES})