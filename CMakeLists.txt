cmake_minimum_required(VERSION 3.28)

project(LiteString C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Google Test requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional options for the Debug build
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")

# Sanitizers for debugging and testing
# GCC does not support all sanitizers, so Clang is recommended for this purpose. Requires llvm-symbolizer.
# The build type should be RelWithDebInfo (or Debug, adjust the variables appropriately) for sanitizers to work properly.
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    # Address, leak, undefined, integer, nullability sanitizers
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS} -fsanitize=address,leak,undefined,integer,nullability -fno-omit-frame-pointer -g")

    # Thread sanitizer, cannot be used with address sanitizer
    #  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS} -fsanitize=thread -fPIE -fno-omit-frame-pointer -g -O1")

    # Memory sanitizer, cannot be used with address sanitizer.
    # set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS} -fsanitize=memory -fPIE -fno-optimize-sibling-calls -fno-omit-frame-pointer -g -O1")
endif ()

add_library(LiteString INTERFACE lite_string.h)

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
