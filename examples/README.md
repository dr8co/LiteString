# Examples of LiteString usage

This directory contains examples of using the LiteString library.

Before building the examples, make sure that the LiteString library is built or installed.

For building the LiteString library, refer to the [README](../README.md) file in the root directory.

## C API

[word stats](./word_stats.c) - Counts the number of characters and words in a text file.

The text file should not be bigger than 1MB.

```bash
# Compile and link the example
gcc -o word_stats word_stats.c /path/to/liblite-string.a -std=c2x

# Run the example
./word_stats blindtext.txt
```

## C++ API

[grep clone](./cheap_grep.cpp) - A simple clone of the `grep` command.

```bash
# Compile and link the example
g++ -o cheap_grep cheap_grep.cpp /path/to/liblite-string.a -std=c++20

# Run the example
./cheap_grep -i "ipsum dolor" blindtext.txt

# The program can also read from standard input, when the file name is replaced with a hyphen
cat blindtext.txt | ./cheap_grep -i "ipsum dolor" -
./cheap_grep -i "lorem ipsum dolor sit amet consectetur adipiscing" - < blindtext.txt
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

For more elaborate examples, refer to the [tests'](../tests) directory.

You can also check [Cachetron](https://github.com/dr8co/Cachetron), a simple cache server,
which uses an earlier version of LiteString for parsing the commands
and for other string manipulations.
