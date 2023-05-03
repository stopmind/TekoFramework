cmake_minimum_required(VERSION 3.25)

project(Teko)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML REQUIRED COMPONENTS system)
if(NOT SFML_FOUND)
    message(SEND_ERROR "Failed to find SFML")
    return()
endif()

include_directories(${SFML_INCLUDE_DIR})
include_directories(include)

add_subdirectory(src)
add_subdirectory(test)