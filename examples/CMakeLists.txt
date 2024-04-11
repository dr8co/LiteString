# C example
add_executable(word_stats word_stats.c)
target_link_libraries(word_stats LiteString)

# C++ example
add_executable(cheap_grep cheap_grep.cpp)
target_link_libraries(cheap_grep LiteString)
