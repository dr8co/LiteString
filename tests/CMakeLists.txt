cmake_minimum_required(VERSION 3.28)

project(LiteString C CXX)

# Test executable
add_executable(testLiteString
        testLiteString.cpp
        testConversion.cpp
        testModifiers.cpp
        testOperations.cpp
        testSearch.cpp)

# Link with gtest
target_link_libraries(testLiteString lite-string gtest gtest_main)

include(GoogleTest)

# Discover tests
gtest_discover_tests(testLiteString)
