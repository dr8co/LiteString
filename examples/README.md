# Examples of LiteString usage

This directory contains examples of using the LiteString library.

Before building the examples, make sure that the LiteString library is built or installed.

For building the LiteString library, refer to the [README](../README.md) file in the root directory.

## C API

[word stats](./word_stats.c) - Counts the number of characters and words in a text file.

The text file should not be bigger than 1MB.

```bash
gcc -o word_stats word_stats.c -L /path/to/libLiteString.a -llite_string
./word_stats blindtext.txt
```

## C++ API

[grep clone](./cheap_grep.cpp) - A simple clone of the `grep` command.

```bash
g++ -o cheap_grep cheap_grep.cpp -L /path/to/libLiteString.a -llite_string
./cheap_grep -i "ipsum dolor" blindtext.txt
```

## Building with CMake

The [CMakeLists.txt](./CMakeLists.txt) file in this directory can be used to build the examples.

```bash
# From this directory (examples), run:
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G Ninja
cmake --build build -j 4
```

The examples can be found in the `build` directory.

```bash
# From this directory (examples), run:
./build/word_stats blindtext.txt
./build/cheap_grep -i "ipsum dolor" blindtext.txt
```
