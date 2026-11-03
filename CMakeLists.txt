cmake_minimum_required(VERSION 3.16)
project(CineSort VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(cinesort ${SOURCES})

# Compiler warnings
if (MSVC)
    target_compile_options(cinesort PRIVATE /W4)
else()
    target_compile_options(cinesort PRIVATE -Wall -Wextra -O2)
endif()
