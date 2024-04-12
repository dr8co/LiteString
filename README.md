# LiteString

## About

A simple byte string library for C (and C++).

LiteString provides an extended set of functions for working with strings.
It is intended to be a lightweight emulation of the C++ `std::string` class,
with a focus on simplicity, performance, and ease of use.

LiteString is written in C and can be used in both C and C++ projects.

## Features

- Simple and easy to use
- Lightweight and fast
- Compatible with C and C++
- No dependencies, just the standard library

## Building

### Prerequisites

- A C23 compiler (such as [GCC 13](https://gcc.gnu.org/) or [Clang 18](https://clang.llvm.org/))
- [CMake 3.28](https://cmake.org/) or later (optional)
- [Ninja](https://ninja-build.org/) (optional)

### Building with CMake (Recommended)

With CMake and Ninja installed, run the following commands:

```bash
# Clone the repository or download the source code.
git clone https://github.com/dr8co/LiteString.git

# Change the working directory to the project directory.
cd LiteString

# Build from the main branch.
git checkout main

# Create a build directory.
mkdir build

# Configure the project.
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -G Ninja

# Build the library.
cmake --build build -j 4
```

Replace `Ninja` with `"Unix Makefiles"` or another generator if Ninja is not available.
The `-G` option can be omitted to use the default generator.

The library will be built as a static library named `liblite-string.a`, in the `build` directory.

### Building Manually

To build the library, run the following commands:

```bash
gcc -c -O3 -std=c23 -o lite_string.o lite_string.c
ar rcs liblite-string.a lite_string.o
```

`clang` can be used instead of `gcc` to compile the source code with Clang.

## Usage

To use the library, include the header file in your source code:

```c
#include "lite_string.h"
```

Compile the source code and link it with the library:

```bash
# C
gcc -std=c2x -O3 -o example example.c /path/to/liblite-string.a
# C++
g++ -std=c++20 -O3 -o example example.cpp /path/to/liblite-string.a
```

Projects using CMake can link the library through the `target_link_libraries` command:

```cmake
target_link_libraries(example /path/to/libLiteString.a)
```

See the [CMakeLists.txt](./examples/CMakeLists.txt) file in the `examples` directory for an example.

## API

The API is designed to be as similar as possible to the C++ std::string class.

Pointer parameters are restrict-qualified by default to indicate that the pointer
does not alias with any other pointer in the same function.
This can help the compiler generate more efficient code.

If pointer aliasing is desired, define the `LITE_STRING_NO_RESTRICT` macro
with an integer value greater than 0 before including the header file.

```c
#define LITE_STRING_NO_RESTRICT 1
#include "lite_string.h"
```

### Types and Constants

A structure is used to represent a string:

```c
struct lite_string {
    char *data;      // A pointer to the character data.
    size_t size;     // The number of characters in the string, not including the null character.
    size_t capacity; // The total number of characters that the string can hold.
};

typedef struct lite_string lite_string;
// The lite_string type.
```

The `lite_string_npos` constant is used to indicate an invalid index:

```c
#define lite_string_npos ((size_t) -1)
// The maximum value of the size_t type.
```

`lite_string_npos` is also used as the return value on failure
in functions that return a `size_t` value.

### Creation and Destruction

A lite_string object is allocated on the heap and must be freed when no longer needed.

```c
lite_string *string_new();
// Creates a new string with an initial capacity of 16.

lite_string *string_new_cstr(const char *restrict cstr);
// Creates a new string from a C-string.

lite_string *string_duplicate(const lite_string *restrict s);
// Creates a copy of a string.

void string_free(lite_string *const restrict s);
// Frees the memory used by a string.
```

### Element access

```c
char string_at(const lite_string *const restrict s, const size_t index);
// Retrieves the character at a given index in the string.

char string_front(const lite_string *const restrict s);
// Retrieves the first character of a string.

char string_back(const lite_string *const restrict s);
// Retrieves the last character of a string.

char *string_data(const lite_string *restrict s);
// Returns a pointer to the underlying character array. Not guaranteed to be null-terminated.

char *string_cstr(const lite_string *const restrict s);
// Returns a pointer to the underlying C-string. Guaranteed to be null-terminated.
```

### Capacity

```c
bool string_empty(const lite_string *const restrict s);
// Checks if the string is empty.

size_t string_size(const lite_string *restrict s);
size_t string_length(const lite_string *const restrict s);
// Returns the length of the string.

size_t string_capacity(const lite_string *const restrict s);
// Returns the capacity of the string.

bool string_reserve(lite_string *const restrict s, size_t size);
// Reserves memory for a string.

bool string_shrink_to_fit(lite_string *const restrict s);
// Frees any unused memory in the string.
```

### Modifiers

```c
void string_clear(lite_string *const restrict s);
// Clears the contents of a string.

bool string_shrink(lite_string *const restrict s, const size_t size);
// Shrinks the string to a specified size. Analogous to the C++ std::string::resize(); function.

bool string_insert_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t index, const size_t count);
// Inserts a specified number of characters from a C-string into a string at a specified index.

bool string_insert_cstr(lite_string *const restrict s, const char *restrict cstr, const size_t index);
// Inserts a C-string into a string at a specified index.

bool string_insert_string(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index);
// Inserts a substring into a string at a specified index.

bool string_insert(lite_string *const restrict s, const size_t index, const char c);
// Inserts a new character at a given index in the string.

bool string_insert_range(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index, const size_t count);
// Inserts a specified number of characters from a substring into a string at a specified index.

bool string_erase(lite_string *const restrict s, const size_t index);
// Removes the character at a given index in the string.

bool string_erase_range(lite_string *restrict s, size_t start, size_t count);
// Removes a specified number of characters from a string, starting from a specified index.

bool string_push_back(lite_string *const restrict s, const char c);
// Appends a character to the end of a string.

void string_pop_back(lite_string *const restrict s);
// Removes the last character from the string.

void string_set(const lite_string *const restrict s, const size_t index, const char c);
// Modifies the character at a given index in the string. Analogous to the C++ std::string::operator[].

bool string_append_range(lite_string *const restrict s1, const lite_string *const restrict s2, const size_t count);
// Appends a specified number of characters from one string to another.

bool string_append(lite_string *const restrict s1, const lite_string *const restrict s2);
// Appends a string to the end of another string.

bool string_append_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t count);
// Appends a specified number of characters from a C-string to a string.

bool string_append_cstr(lite_string *const restrict s, const char *const restrict cstr);
// Appends a C-string to the end of a string.

lite_string * string_concat(const lite_string *const restrict s1, const lite_string *const restrict s2);
// Concatenates two strings.

bool string_copy_buffer(const lite_string *const restrict s, char *buf);
// Copies the characters from a string to a buffer.

bool string_copy(const lite_string *const restrict src, lite_string *const restrict dest);
// Copies the contents of one string to another.

bool string_swap(lite_string *const restrict s1, lite_string *const restrict s2);
// Swaps the contents of two strings.

bool string_replace(lite_string *restrict s, const lite_string *restrict old_sub,
                    const lite_string *restrict new_sub);
// Replaces all occurrences of a substring in a string with another substring.

void string_replace_char(const lite_string *restrict s, char old_char, char new_char);
// Replaces all occurrences of a character in a string with another character.

bool string_replace_cstr(lite_string *restrict s, const char *restrict old_cstr,
                         const char *restrict new_cstr);
// Replaces all occurrences of a C-string in a string with another C-string.

void string_reverse(const lite_string *restrict s);
// Reverses the characters in a string.
```

### Conversion

```c
void string_to_lower(const lite_string *restrict s);
// Converts a string to lowercase.

void string_to_upper(const lite_string *restrict s);
// Converts a string to uppercase.

void string_to_title(const lite_string *restrict s);
// Converts a string to title case.

long long string_to_ll(const lite_string *restrict s);
// Converts a string to a long long integer.

unsigned long long string_to_ull(const lite_string *restrict s);
// Converts a string to an unsigned long long integer.

long string_to_l(const lite_string *restrict s);
// Converts a string to a long integer.

unsigned long string_to_ul(const lite_string *restrict s);
// Converts a string to an unsigned long integer.

int string_to_int(const lite_string *restrict s);
// Converts a string to an integer.

unsigned int string_to_uint(const lite_string *restrict s);
// Converts a string to an unsigned integer.

double string_to_double(const lite_string *restrict s);
// Converts a string to a double-precision floating-point number.

float string_to_float(const lite_string *restrict s);
// Converts a string to a single-precision floating-point number.

long double string_to_ldouble(const lite_string *restrict s);
// Converts a string to a long double-precision floating-point number.

lite_string *string_from_l(long value);
// Converts a long integer to a string.

lite_string *string_from_ll(long long value);
// Converts a long long integer to a string.

lite_string *string_from_ul(unsigned long value);
// Converts an unsigned long integer to a string.

lite_string *string_from_ull(unsigned long long value);
// Converts an unsigned long long integer to a string.

lite_string *string_from_int(int value);
// Converts an integer to a string.

lite_string *string_from_uint(unsigned int value);
// Converts an unsigned integer to a string.

lite_string *string_from_double(double value);
// Converts a double-precision floating-point number to a string.

lite_string *string_from_float(float value);
// Converts a single-precision floating-point number to a string.

lite_string *string_from_ldouble(long double value);
// Converts a long double-precision floating-point number to a string.
```

### Search

```c
size_t string_find_from(const lite_string *const restrict s, const lite_string *const restrict sub, const size_t start);
// Finds the first occurrence of a substring in a string, starting from a specified index.

size_t string_find(const lite_string *const restrict s, const lite_string *const restrict sub);
// Finds the first occurrence of a substring in a string.

size_t string_rfind(const lite_string *const restrict s, const lite_string *const restrict sub);
// Finds the last occurrence of a substring in a string.

size_t string_find_cstr_from(const lite_string *const restrict s, const char *const restrict cstr, const size_t start);
// Finds the first occurrence of a C-string in a string, starting from a specified index.

size_t string_rfind_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Finds the last occurrence of a C-string in a string.

size_t string_find_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Finds the first occurrence of a C-string in a string.

size_t string_find_last_of(const lite_string *const restrict s, const char c);
// Finds the last occurrence of a character in a string.

size_t string_find_last_not_of(const lite_string *const restrict s, const char c);
// Finds the last occurrence of a character that does not match the specified character in a string.

size_t string_find_first_from(const lite_string *const restrict s, const char c, const size_t start);
// Finds the first occurrence of a character in a string, starting from a specified index.

size_t string_find_first_of(const lite_string *const restrict s, const char c);
// Finds the first occurrence of a character in a string.

size_t string_find_first_not_of(const lite_string *const restrict s, const char c);
// Finds the first occurrence of a character that does not match the specified character in a string.
```

### Operations

```c
bool string_compare(const lite_string *const restrict s1, const lite_string *const restrict s2);
// Compares two strings for equality.

bool string_case_compare(const lite_string *const restrict s1, const lite_string *const restrict s2);
// Compares two strings for equality, ignoring case.

bool string_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Compares a string with a C-string for equality.

bool string_case_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Compares a string with a C-string for equality, ignoring case.

bool string_contains_char(const lite_string *const restrict s, const char c);
// Checks if a string contains a specified character.

bool string_contains(const lite_string *const restrict s, const lite_string *const restrict sub);
// Checks if a string contains a specified substring.

bool string_contains_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Checks if a string contains a specified C-string.

bool string_starts_with(const lite_string *const restrict s, const lite_string *const restrict sub);
// Checks if a string starts with a specified substring.

bool string_starts_with_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Checks if a string starts with a specified C-string.

bool string_ends_with(const lite_string *const restrict s, const lite_string *const restrict sub);
// Checks if a string ends with a specified substring.

bool string_ends_with_cstr(const lite_string *const restrict s, const char *const restrict cstr);
// Checks if a string ends with a specified C-string.

lite_string *string_substr(const lite_string *const restrict s, const size_t start, const size_t len);
// Retrieves a substring from the string.
```

### Error Handling

The library does not use exceptions.
Instead, functions return `bool` values to indicate success or failure.

Functions that return numeric values return `SIZE_MAX` on failure,
while those that return pointers return `nullptr`.

## Examples

Basic usage of the library:

```c
#include "lite_string.h"
#include <stdio.h>

int main() {
    lite_string *s = string_new();
    string_append_cstr(s, "Hello, ");
    string_append_cstr(s, "world!");
    printf("%s\n", string_cstr(s););
    string_free(s);
    return 0;
}
```

More examples can be found in the [examples'](./examples) directory.

## License

LiteString is released under the MIT License. See `LICENSE` for more information.
