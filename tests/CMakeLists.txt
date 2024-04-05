# Test executable
add_executable(testLiteString
        testLiteString.cpp
        ../lite_str.h
        ../lite_str.c)

# Link with gtest
target_link_libraries(testLiteString gtest gtest_main)

include(GoogleTest)

# Discover tests
gtest_discover_tests(testLiteString)
