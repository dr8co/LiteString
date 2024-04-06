cmake_minimum_required(VERSION 3.28)

project(LiteStr C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Google Test requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional options for the Debug build
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")

add_library(LiteStr STATIC lite_str.h lite_str.c)

# Google Test
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f10e11fb27301fba21caa71030bb5024e67aa135.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# Tests
add_subdirectory(tests)
