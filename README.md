# LiteString

## About

A simple string library for C (and C++).

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

A C23 compiler (such as [GCC 13](https://gcc.gnu.org/) or [Clang 18](https://clang.llvm.org/))
is required to build the library.

To build the library, run the following commands:

[//]: # (TODO: Complete the build instructions.)


## Usage

To use the library, include the header file in your source code:

```c
#include "lite_string.h"
```

Compile the source code and link it with the library:

```bash
gcc example.c -o example -llite_string
```

Projects using CMake can link the library with the following commands:

[//]: # (TODO: Add CMake instructions.)

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

### Types

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

### Creation and Destruction

A lite_string object is allocated on the heap and must be freed when no longer needed.

```c
lite_string *string_new()
// Creates a new string with an initial capacity of 16.

void string_free(lite_string *const restrict s)
// Frees the memory used by a string.
```

### Element access

```c
char string_at(const lite_string *const restrict s, const size_t index)
// Retrieves the character at a given index in the string.

char string_front(const lite_string *const restrict s)
// Retrieves the first character of a string.

char string_back(const lite_string *const restrict s)
// Retrieves the last character of a string.

char *string_cstr(const lite_string *const restrict s)
// Returns a pointer to the underlying C-string.
```

### Capacity

```c
bool string_empty(const lite_string *const restrict s)
// Checks if the string is empty.

size_t string_length(const lite_string *const restrict s)
// Returns the length of the string.

size_t string_capacity(const lite_string *const restrict s)
// Returns the capacity of the string.

bool string_reserve(lite_string *const restrict s, size_t size)
// Reserves memory for a string.

bool string_shrink_to_fit(lite_string *const restrict s)
// Frees any unused memory in the string.
```

### Modifiers

```c
void string_clear(lite_string *const restrict s)
// Clears the contents of a string.

bool string_shrink(lite_string *const restrict s, const size_t size)
// Shrinks the string to a specified size. Analogous to the C++ std::string::resize() function.

bool string_insert_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t index, const size_t count)
// Inserts a specified number of characters from a C-string into a string at a specified index.

bool string_insert_cstr(lite_string *const restrict s, const char *restrict cstr, const size_t index)
// Inserts a C-string into a string at a specified index.

bool string_insert_string(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index)
// Inserts a substring into a string at a specified index.

bool string_insert(lite_string *const restrict s, const size_t index, const char c)
// Inserts a new character at a given index in the string.

bool string_insert_range(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index, const size_t count)
// Inserts a specified number of characters from a substring into a string at a specified index.

bool string_erase(lite_string *const restrict s, const size_t index)
// Removes the character at a given index in the string.

bool string_push_back(lite_string *const restrict s, const char c)
// Appends a character to the end of a string.

void string_pop_back(lite_string *const restrict s)
// Removes the last character from the string.

void string_set(const lite_string *const restrict s, const size_t index, const char c)
// Modifies the character at a given index in the string. Analogous to the C++ std::string::operator[].

bool string_append_range(lite_string *const restrict s1, const lite_string *const restrict s2, const size_t count)
// Appends a specified number of characters from one string to another.

bool string_append(lite_string *const restrict s1, const lite_string *const restrict s2)
// Appends a string to the end of another string.

bool string_append_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t count)
// Appends a specified number of characters from a C-string to a string.

bool string_append_cstr(lite_string *const restrict s, const char *const restrict cstr)
// Appends a C-string to the end of a string.

lite_string * string_concat(const lite_string *const restrict s1, const lite_string *const restrict s2)
// Concatenates two strings.

bool string_copy_buffer(const lite_string *const restrict s, char *buf)
// Copies the characters from a string to a buffer.

bool string_copy(const lite_string *const restrict src, lite_string *const restrict dest)
// Copies the contents of one string to another.

bool string_swap(lite_string *const restrict s1, lite_string *const restrict s2)
// Swaps the contents of two strings.
```

### Search

```c
size_t string_find_substr_from(const lite_string *const restrict s, const lite_string *const restrict sub, const size_t start)
// Finds the first occurrence of a substring in a string, starting from a specified index.

size_t string_find_substr(const lite_string *const restrict s, const lite_string *const restrict sub)
// Finds the first occurrence of a substring in a string.

size_t string_rfind_substr(const lite_string *const restrict s, const lite_string *const restrict sub)
// Finds the last occurrence of a substring in a string.

size_t string_find_substr_cstr_from(const lite_string *const restrict s, const char *const restrict cstr, const size_t start)
// Finds the first occurrence of a C-string in a string, starting from a specified index.

size_t string_rfind_substr_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Finds the last occurrence of a C-string in a string.

size_t string_find_substr_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Finds the first occurrence of a C-string in a string.

size_t string_find_last_of(const lite_string *const restrict s, const char c)
// Finds the last occurrence of a character in a string.

size_t string_find_last_not_of(const lite_string *const restrict s, const char c)
// Finds the last occurrence of a character that does not match the specified character in a string.

size_t string_find_first_from(const lite_string *const restrict s, const char c, const size_t start)
// Finds the first occurrence of a character in a string, starting from a specified index.

size_t string_find_first_of(const lite_string *const restrict s, const char c)
// Finds the first occurrence of a character in a string.

size_t string_find_first_not_of(const lite_string *const restrict s, const char c)
// Finds the first occurrence of a character that does not match the specified character in a string.
```

### Operations

```c
bool string_compare(const lite_string *const restrict s1, const lite_string *const restrict s2)
// Compares two strings for equality.

bool string_case_compare(const lite_string *const restrict s1, const lite_string *const restrict s2)
// Compares two strings for equality, ignoring case.

bool string_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Compares a string with a C-string for equality.

bool string_case_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Compares a string with a C-string for equality, ignoring case.

bool string_contains_char(const lite_string *const restrict s, const char c)
// Checks if a string contains a specified character.

bool string_contains(const lite_string *const restrict s, const lite_string *const restrict sub)
// Checks if a string contains a specified substring.

bool string_contains_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Checks if a string contains a specified C-string.

bool string_starts_with(const lite_string *const restrict s, const lite_string *const restrict sub)
// Checks if a string starts with a specified substring.

bool string_starts_with_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Checks if a string starts with a specified C-string.

bool string_ends_with(const lite_string *const restrict s, const lite_string *const restrict sub)
// Checks if a string ends with a specified substring.

bool string_ends_with_cstr(const lite_string *const restrict s, const char *const restrict cstr)
// Checks if a string ends with a specified C-string.

lite_string * string_substr(const lite_string *const restrict s, const size_t start, const size_t len)
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
    printf("%s\n", string_cstr(s));
    string_free(s);
    return 0;
}
```

More examples can be found in the `examples` directory.

## License

LiteString is released under the MIT License. See `LICENSE` for more information.
```
