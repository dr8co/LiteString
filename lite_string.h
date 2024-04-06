#pragma once

#if LITE_NO_RESTRICT_

// Ignore the warning for redefining the 'restrict' keyword
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif // __clang__

#define restrict

// Restore Clang warnings
#if __clang__
#pragma clang diagnostic pop
#endif // __clang__
#endif // LITE_NO_RESTRICT_

#if __cplusplus
#if !LITE_NO_RESTRICT_ // The keyword has not been redefined
#if __GNUC__ || __clang__ || _MSC_VER // Support for '__restrict'

// Ignore the warning for redefining the 'restrict' keyword
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif // __clang__

#define restrict __restrict
#else // No support for '__restrict'
#define restrict
#endif // __GNUC__ || __clang__ || _MSC_VER

// Restore Clang warnings
#if __clang__
#pragma clang diagnostic pop
#endif

#endif // LITE_NO_RESTRICT_

extern "C" {
#endif // __cplusplus

#include <stddef.h>


/**
 * @brief A simple emulation of a C++ string in C.
 *
 * The data is stored as a pointer to a dynamically allocated array of characters.\n
 * The capacity represents the total number of characters that the string can hold without needing to be resized.\n
 * When the size reaches the capacity, the string is resized to a larger capacity to accommodate more characters.
 */
struct lite_string {
    char *data;      ///< A pointer to the character data.
    size_t size;     ///< The number of characters in the string, not including the null character.
    size_t capacity; ///< The total number of characters that the string can hold.
};

typedef struct lite_string lite_string;


[[nodiscard]] lite_string *string_new();

void string_free(lite_string *restrict s);

bool string_reserve(lite_string *restrict s, size_t size);

bool string_push_back(lite_string *restrict s, char c);

char string_at(const lite_string *restrict s, size_t index);

void string_pop_back(lite_string *restrict s);

bool string_empty(const lite_string *restrict s);

bool string_erase(lite_string *restrict s, size_t index);

char string_back(const lite_string *restrict s);

char string_front(const lite_string *restrict s);

bool string_compare(const lite_string *restrict s1, const lite_string *restrict s2);

size_t string_length(const lite_string *restrict s);

size_t string_capacity(const lite_string *restrict s);

void string_clear(lite_string *restrict s);

bool string_insert(lite_string *restrict s, size_t index, char c);

void string_set(const lite_string *restrict s, size_t index, char c);

[[nodiscard]] lite_string *string_substr(const lite_string *restrict s, size_t start, size_t len);

[[nodiscard]] lite_string *string_concat(const lite_string *restrict s1, const lite_string *restrict s2);

bool string_append_range(lite_string *restrict s1, const lite_string *restrict s2, size_t count);

bool string_append(lite_string *restrict s1, const lite_string *restrict s2);

bool string_append_cstr(lite_string *restrict s, const char *restrict cstr);

[[nodiscard]] char *string_cstr(const lite_string *restrict s);

bool string_compare_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_insert_cstr(lite_string *restrict s, const char *restrict cstr, size_t index);

bool string_append_cstr_range(lite_string *restrict s, const char *restrict cstr, size_t count);

bool string_copy_buffer(const lite_string *restrict s, char *buf);

bool string_copy(const lite_string *restrict src, lite_string *restrict dest);

bool string_case_compare(const lite_string *restrict s1, const lite_string *restrict s2);

bool string_case_compare_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_swap(lite_string *restrict s1, lite_string *restrict s2);

bool string_insert_cstr_range(lite_string *restrict s, const char *restrict cstr, size_t index, size_t count);

bool string_insert_range(lite_string *restrict s, const lite_string *restrict sub, size_t index, size_t count);

bool string_insert_string(lite_string *restrict s, const lite_string *restrict sub, size_t index);

size_t string_find_last_of(const lite_string *restrict s, char c);

size_t string_find_last_not_of(const lite_string *restrict s, char c);

size_t string_find_first_from(const lite_string *restrict s, char c, size_t start);

size_t string_find_first_of(const lite_string *restrict s, char c);

size_t string_find_first_not_of(const lite_string *restrict s, char c);

size_t string_find_substr_from(const lite_string *restrict s, const lite_string *restrict sub, size_t start);

size_t string_find_substr(const lite_string *restrict s, const lite_string *restrict sub);

size_t string_rfind_substr(const lite_string *restrict s, const lite_string *restrict sub);

size_t string_find_substr_cstr_from(const lite_string *restrict s, const char *restrict cstr, size_t start);

size_t string_rfind_substr_cstr(const lite_string *restrict s, const char *restrict cstr);

size_t string_find_substr_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_contains_char(const lite_string *restrict s, char c);

bool string_contains(const lite_string *restrict s, const lite_string *restrict sub);

bool string_contains_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_starts_with(const lite_string *restrict s, const lite_string *restrict sub);

bool string_starts_with_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_ends_with(const lite_string *restrict s, const lite_string *restrict sub);

bool string_ends_with_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_shrink(lite_string *restrict s, size_t size);

bool string_shrink_to_fit(lite_string *restrict s);

#if __cplusplus
}
#endif
