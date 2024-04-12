cmake_minimum_required(VERSION 3.28)

project(LiteString C CXX)

# C example
add_executable(word_stats word_stats.c)
target_link_libraries(word_stats lite-string)

# C++ example
add_executable(cheap_grep cheap_grep.cpp)
target_link_libraries(cheap_grep lite-string)
