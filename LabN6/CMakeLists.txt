cmake_minimum_required(VERSION 3.25)
project(LabN6 C)

set(CMAKE_C_STANDARD 11)

# Find OpenSSL package
find_package(OpenSSL REQUIRED)

# Include OpenSSL headers
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(LabN6 main.c)

target_link_libraries(LabN6 ${OPENSSL_LIBRARIES})