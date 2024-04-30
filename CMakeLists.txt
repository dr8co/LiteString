cmake_minimum_required(VERSION 3.28)

project(LiteString
        VERSION 0.1.0
        DESCRIPTION "A lightweight byte string library for C"
        HOMEPAGE_URL "https://github.com/dr8co/LiteString"
        LANGUAGES C CXX)

# C23 is not supported by MSVC, as of cl 19.37.32824
if (NOT MSVC)
    set(CMAKE_C_STANDARD 23)
endif ()

set(CMAKE_C_STANDARD_REQUIRED ON)

# Google Test requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTING "Build tests" OFF)

# MSVC Runtime Library and other settings
if (MSVC)
    if (BUILD_SHARED_LIBS)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    else ()
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    endif ()
endif ()

# Additional compile options for the Debug build
if (NOT MSVC AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(
                -Wall
                -Wextra
                -Werror
                -Wpedantic
                -g
        )
    endif ()
endif ()

# Sanitizers for debugging and testing
# GCC does not support all sanitizers, so Clang is recommended for this purpose. Requires llvm-symbolizer.
# The build type should be RelWithDebInfo (or Debug, adjust the variables appropriately) for sanitizers to work properly.
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang")
    # Common flags for all sanitizers
    set(sanitizer_common_flags "-fno-omit-frame-pointer -g -O1")

    # Address, leak, undefined, integer, nullability sanitizers
    set(address_sanitizer_flags "-fsanitize=address,leak,undefined,integer,nullability")

    # Thread sanitizer, cannot be used with address sanitizer
    set(thread_sanitizer_flags "-fsanitize=thread -fPIE")

    # Memory sanitizer, cannot be used with address sanitizer.
    set(memory_sanitizer_flags "-fsanitize=memory -fPIE -fno-optimize-sibling-calls")

    # Add flags for Release with Debug Info build
    if (CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        add_compile_options(
                ${sanitizer_common_flags}
                ${address_sanitizer_flags}
        )
    endif ()
endif ()

# Add the CMake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_library(lite-string)
target_sources(lite-string PRIVATE lite_string.c)
add_library(LiteString::lite-string ALIAS lite-string)

# Set the include directory for the library
target_include_directories(lite-string PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(lite-string PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER lite_string.h
)

# Additional definitions for the library
if (${CMAKE_C_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_C_COMPILER_ID} STREQUAL "GNU")
    target_compile_definitions(lite-string PRIVATE _GNU_SOURCE)
endif ()

include(GNUInstallDirs)

install(TARGETS lite-string
        EXPORT LiteStringTargets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT libraries
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT libraries
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}" COMPONENT libraries
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" COMPONENT headers
)

install(EXPORT LiteStringTargets
        FILE LiteStringTargets.cmake
        NAMESPACE LiteString::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString"
        COMPONENT CMakeConfig
)

include(CMakePackageConfigHelpers)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/input_files/LiteStringConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString")

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY AnyNewerVersion)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/LiteStringConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/LiteString"
        COMPONENT CMakeConfig
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input_files/liblite-string.pc.in"
        "${CMAKE_CURRENT_BINARY_DIR}/liblite-string.pc" @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/liblite-string.pc"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
        COMPONENT pkgconfig
)

# Notify about MinGW builds in the version_info.txt file
if (MINGW)
    set(C_COMPILER_EXTRA_INFO "(For MinGW)")
endif ()

# Get the current date and time in UTC
string(TIMESTAMP CURRENT_DATE "%Y-%m-%d %H:%M:%S" UTC)

# Get the build flags
set(FLAGS_VAR "CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}")
string(TOUPPER "${FLAGS_VAR}" FLAGS_VAR)
string(CONFIGURE "@${FLAGS_VAR}@" BUILD_FLAGS)

# Configure the version_info.txt file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/input_files/version_info.txt.in"
        "${CMAKE_CURRENT_BINARY_DIR}/version_info.txt" @ONLY)

# Install the version_info.txt file
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/version_info.txt"
        DESTINATION "${CMAKE_INSTALL_DATADIR}/LiteString"
        COMPONENT data
)

# Examples
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

# Testing
if (BUILD_TESTING)
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
    add_subdirectory(tests)
endif ()

include(Packing)
