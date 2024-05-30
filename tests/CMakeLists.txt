cmake_minimum_required(VERSION 3.28)

project(LiteString C CXX)

# Test executable
add_executable(testLiteString)
target_sources(testLiteString PRIVATE
        testGeneralStuff.cpp
        testConversion.cpp
        testModifiers.cpp
        testOperations.cpp
        testSearch.cpp
)

if (GTest_ManualFetch)
    target_include_directories(testLiteString PRIVATE ${GTest_INCLUDE_DIRS})
endif ()

# Link with gtest
target_link_libraries(testLiteString PRIVATE
        lite-string GTest::gtest GTest::gtest_main)

include(GoogleTest)

# Discover tests
gtest_discover_tests(testLiteString)
