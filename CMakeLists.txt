cmake_minimum_required(VERSION 3.10)
project(check_kit)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(check_kit
    src/main.cpp
    src/document.cpp
    src/kits.cpp
    src/path_utils.cpp
)

target_include_directories(check_kit PRIVATE src)