# Test executable
add_executable(testLiteString testLiteString.cpp)

# Link with gtest
target_link_libraries(testLiteString LiteStr gtest gtest_main)

include(GoogleTest)

# Discover tests
gtest_discover_tests(testLiteString)
