#pragma once

#if LITE_STRING_NO_RESTRICT

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
#endif // LITE_STRING_NO_RESTRICT

#if __cplusplus
#if !LITE_STRING_NO_RESTRICT // The keyword has not been redefined
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

#endif // LITE_STRING_NO_RESTRICT

extern "C" {
#endif // __cplusplus

#include <stddef.h>

#if __STDC_VERSION__ < 202311L
#include <stdbool.h>
#endif
#define lite_string_npos ((size_t) -1)

#ifndef __has_c_attribute
#define __has_c_attribute(x) 0  // Compatibility with non-gnu compilers
#endif

#if __has_c_attribute(nodiscard)
#define LITE_ATTR_NODISCARD [[__nodiscard__]]
#else
#define LITE_ATTR_NODISCARD
#endif

#if __has_c_attribute(gnu::hot)
#define LITE_ATTR_HOT [[gnu::hot]]
#else
#define LITE_ATTR_HOT
#endif

#if __has_c_attribute(reproducible)
#define LITE_ATTR_REPRODUCIBLE [[__reproducible__]]
#elif __has_c_attribute(gnu::pure)
#define LITE_ATTR_REPRODUCIBLE [[gnu::pure]]
#else
#define LITE_ATTR_REPRODUCIBLE
#endif

#if __has_c_attribute(unsequenced)
#define LITE_ATTR_UNSEQUENCED [[__unsequenced__]]
#elif __has_c_attribute(gnu::const)
#define LITE_ATTR_UNSEQUENCED [[gnu::const]]
#else
#define LITE_ATTR_UNSEQUENCED
#endif


/**
 * @brief A simple emulation of a C++ string in C.
 *
 * The data is stored as a pointer to a dynamically allocated array of characters.\n
 * The capacity represents the total number of characters that the string can hold without needing to be resized.\n
 * When the size reaches the capacity, the string is resized to a larger capacity to accommodate more characters.
 */
struct lite_string {
    char *data; ///< A pointer to the character data.
    size_t size; ///< The number of characters in the string, not including the null character.
    size_t capacity; ///< The total number of characters that the string can hold.
};

typedef struct lite_string lite_string;


LITE_ATTR_NODISCARD LITE_ATTR_HOT lite_string *string_new();

LITE_ATTR_HOT void string_free(lite_string *restrict s);

LITE_ATTR_HOT bool string_reserve(lite_string *restrict s, size_t size);

bool string_push_back(lite_string *restrict s, char c);

char string_at(const lite_string *restrict s, size_t index);

void string_pop_back(lite_string *restrict s);

bool string_empty(const lite_string *restrict s);

bool string_erase(lite_string *restrict s, size_t index);

char string_back(const lite_string *restrict s);

char string_front(const lite_string *restrict s);

bool string_compare(const lite_string *restrict s1, const lite_string *restrict s2);

LITE_ATTR_HOT size_t string_length(const lite_string *restrict s);

LITE_ATTR_HOT size_t string_size(const lite_string *restrict s);

size_t string_capacity(const lite_string *restrict s);

void string_clear(lite_string *restrict s);

bool string_insert(lite_string *restrict s, size_t index, char c);

void string_set(const lite_string *restrict s, size_t index, char c);

LITE_ATTR_NODISCARD lite_string *string_substr(const lite_string *restrict s, size_t start, size_t len);

LITE_ATTR_NODISCARD lite_string *string_concat(const lite_string *restrict s1, const lite_string *restrict s2);

bool string_append_range(lite_string *restrict s1, const lite_string *restrict s2, size_t count);

bool string_append(lite_string *restrict s1, const lite_string *restrict s2);

bool string_append_cstr(lite_string *restrict s, const char *restrict cstr);

LITE_ATTR_HOT char *string_cstr(lite_string *restrict s);

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

size_t string_find_from(const lite_string *restrict s, const lite_string *restrict sub, size_t start);

size_t string_find(const lite_string *restrict s, const lite_string *restrict sub);

size_t string_rfind(const lite_string *restrict s, const lite_string *restrict sub);

size_t string_find_cstr_from(const lite_string *restrict s, const char *restrict cstr, size_t start);

size_t string_rfind_cstr(const lite_string *restrict s, const char *restrict cstr);

size_t string_find_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_contains_char(const lite_string *restrict s, char c);

bool string_contains(const lite_string *restrict s, const lite_string *restrict sub);

bool string_contains_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_starts_with(const lite_string *restrict s, const lite_string *restrict sub);

bool string_starts_with_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_ends_with(const lite_string *restrict s, const lite_string *restrict sub);

bool string_ends_with_cstr(const lite_string *restrict s, const char *restrict cstr);

bool string_shrink(lite_string *restrict s, size_t size);

bool string_shrink_to_fit(lite_string *restrict s);

void string_to_lower(const lite_string *restrict s);

void string_to_upper(const lite_string *restrict s);

void string_to_title(const lite_string *restrict s);

LITE_ATTR_NODISCARD LITE_ATTR_HOT lite_string *string_new_cstr(const char *restrict cstr);

bool string_replace(lite_string *restrict s, const lite_string *restrict old_sub,
                    const lite_string *restrict new_sub);

void string_replace_char(const lite_string *restrict s, char old_char, char new_char);

bool string_replace_cstr(lite_string *restrict s, const char *restrict old_cstr,
                         const char *restrict new_cstr);

bool string_erase_range(lite_string *restrict s, size_t start, size_t count);

LITE_ATTR_NODISCARD lite_string *string_duplicate(const lite_string *restrict s);

void string_reverse(const lite_string *restrict s);

long long string_to_ll(lite_string *restrict s);

unsigned long long string_to_ull(lite_string *restrict s);

long string_to_l(lite_string *restrict s);

unsigned long string_to_ul(lite_string *restrict s);

int string_to_int(lite_string *restrict s);

unsigned int string_to_uint(lite_string *restrict s);

double string_to_double(lite_string *restrict s);

float string_to_float(lite_string *restrict s);

long double string_to_ldouble(lite_string *restrict s);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_l(long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ll(long long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ul(unsigned long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ull(unsigned long long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_int(int value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_uint(unsigned int value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_double(double value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_float(float value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ldouble(long double value);

#if __cplusplus
}
#endif
