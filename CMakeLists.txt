cmake_minimum_required(VERSION 3.28)

project(LiteString
        VERSION 0.1.0
        DESCRIPTION "A lightweight byte string library for C"
        HOMEPAGE_URL "https://github.com/dr8co/LiteString"
        LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Google Test requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional options for the Debug build
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "AppleClang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -g")
endif ()

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

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(lite-string lite_string.c lite_string.h)
add_library(LiteString::lite-string ALIAS lite-string)

# Set the include directory for the library
target_include_directories(lite-string PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(lite-string PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER lite_string.h)

# Additional definitions for the library
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    target_compile_definitions(lite-string PRIVATE _GNU_SOURCE)
endif ()

include(GNUInstallDirs)

install(TARGETS lite-string
        EXPORT LiteStringTargets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(EXPORT LiteStringTargets
        FILE LiteStringTargets.cmake
        NAMESPACE LiteString::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString")

include(CMakePackageConfigHelpers)

configure_package_config_file(LiteStringConfig.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString")

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY AnyNewerVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString")

configure_file(liblite-string.pc.in liblite-string.pc @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/liblite-string.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")


# Examples
add_subdirectory(examples)

# Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/f10e11fb27301fba21caa71030bb5024e67aa135.zip)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()

enable_testing()

# Tests
add_subdirectory(tests)

include(Packing)
