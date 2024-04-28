#pragma once

// Library version
#define _lite_string_major 0L ///< LiteString major version.
#define _lite_string_minor 1L ///< LiteString minor version.
#define _lite_string_patch 0L ///< LiteString patch version.

/// The LiteString version as a single integer.
#define _lite_string_version (_lite_string_major * 10000L + _lite_string_minor * 100L + _lite_string_patch)

// Check version compatibility requirements
#ifdef LITE_STRING_REQUIRE_MIN_VERSION
#if (LITE_STRING_REQUIRE_MIN_VERSION + 0) == 0
#if _MSC_VER && !defined(__clang__) // MSVC does not have '#warning', but clang-cl does
#pragma message ("WARNING: Lite String version requirement is enabled, but the version is not specified!")
#else
#warning "Lite String version requirement is enabled, but the version is not specified!"
#endif // _MSC_VER && !defined(__clang__)
#else
#if _lite_string_version < LITE_STRING_REQUIRE_MIN_VERSION
#error "Lite String version is lower than required!"
#endif // _lite_string_version < LITE_STRING_REQUIRE_MIN_VERSION
#endif // (LITE_STRING_REQUIRE_MIN_VERSION + 0) == 0
#endif // LITE_STRING_REQUIRE_MIN_VERSION

#ifndef LITE_STRING_NO_RESTRICT
#define LITE_STRING_NO_RESTRICT 0
#endif // LITE_STRING_NO_RESTRICT

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

#if defined(__cplusplus) && __cplusplus
#if !LITE_STRING_NO_RESTRICT // The keyword has not been redefined
#if __GNUC__ || __clang__ || _MSC_VER // Support for '__restrict' in C++

// Ignore the warning for redefining the 'restrict' keyword (So far, only Clang has this warning)
#if __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wkeyword-macro"
#endif // __clang__

#define restrict __restrict // Use '__restrict' in C++ for GCC, Clang, and MSVC
#else // Support for C++ '__restrict' is unknown on this compiler
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

#define lite_string_npos ((size_t) -1)

#ifdef __has_attribute
#define HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#define HAS_ATTRIBUTE(x) 0
#endif // __has_attribute

#ifdef __has_c_attribute
#define HAS_C_ATTRIBUTE(x) __has_c_attribute(x)
#else
#define HAS_C_ATTRIBUTE(x) HAS_ATTRIBUTE(x)
#endif // __has_c_attribute

#if __STDC_VERSION__ >= 202311L // C23 is supported
#if HAS_C_ATTRIBUTE(nodiscard) // C23 'nodiscard' attribute
#define LITE_ATTR_NODISCARD [[__nodiscard__]]
#elif HAS_ATTRIBUTE(warn_unused_result) // GNU 'warn_unused_result' attribute
#define LITE_ATTR_NODISCARD [[gnu::warn_unused_result]]
#else
#define LITE_ATTR_NODISCARD
#endif // HAS_C_ATTRIBUTE(nodiscard)

#if HAS_ATTRIBUTE(hot) // GNU 'hot' attribute
#define LITE_ATTR_HOT [[gnu::hot]]
#else
#define LITE_ATTR_HOT
#endif // HAS_ATTRIBUTE(hot)

#if HAS_C_ATTRIBUTE(reproducible) // C23 'reproducible' attribute
#define LITE_ATTR_REPRODUCIBLE [[__reproducible__]]
#elif HAS_ATTRIBUTE(pure) // GNU 'pure' attribute as a substitute
#define LITE_ATTR_REPRODUCIBLE [[gnu::pure]]
#else
#define LITE_ATTR_REPRODUCIBLE
#endif // HAS_C_ATTRIBUTE(reproducible)

#if HAS_C_ATTRIBUTE(unsequenced) // C23 'unsequenced' attribute
#define LITE_ATTR_UNSEQUENCED [[__unsequenced__]]
#elif HAS_ATTRIBUTE(__const__)  // GNU 'const' attribute as a substitute
#define LITE_ATTR_UNSEQUENCED [[gnu::const]]
#else
#define LITE_ATTR_UNSEQUENCED
#endif // HAS_C_ATTRIBUTE(unsequenced)

#if HAS_ATTRIBUTE(nothrow) // GNU 'nothrow' attribute
#define LITE_ATTR_NOEXCEPT [[gnu::nothrow]]
#elif _MSC_VER
#define LITE_ATTR_NOEXCEPT __declspec(nothrow) // MSVC equivalent
#else
#define LITE_ATTR_NOEXCEPT
#endif // HAS_ATTRIBUTE(nothrow)

#else // C23 is not supported
#ifndef __cplusplus
#include <stdbool.h>
#define nullptr ((void *) 0)
#endif // __cplusplus

#if HAS_ATTRIBUTE(__warn_unused_result__) // GNU 'warn_unused_result' attribute, pre-C23 syntax
#define LITE_ATTR_NODISCARD __attribute__((__warn_unused_result__))
#else
#define LITE_ATTR_NODISCARD
#endif // HAS_ATTRIBUTE(__warn_unused_result__)

#if HAS_ATTRIBUTE(__hot__) // GNU 'hot' attribute
#define LITE_ATTR_HOT __attribute__((__hot__))
#else
#define LITE_ATTR_HOT
#endif // HAS_ATTRIBUTE(__hot__)

#if HAS_ATTRIBUTE(__pure__) // GNU 'pure' attribute
#define LITE_ATTR_REPRODUCIBLE __attribute__((__pure__))
#else
#define LITE_ATTR_REPRODUCIBLE
#endif // HAS_ATTRIBUTE(__pure__)

#if HAS_ATTRIBUTE(__const__) // GNU 'const' attribute
#define LITE_ATTR_UNSEQUENCED __attribute__((__const__))
#else
#define LITE_ATTR_UNSEQUENCED
#endif // HAS_ATTRIBUTE(__const__)

#if HAS_ATTRIBUTE(__nothrow__) // GNU 'nothrow' attribute
#define LITE_ATTR_NOEXCEPT __attribute__((__nothrow__))
#elif _MSC_VER
#define LITE_ATTR_NOEXCEPT __declspec(nothrow) // MSVC equivalent
#else
#define LITE_ATTR_NOEXCEPT
#endif // HAS_ATTRIBUTE(nothrow)

#endif // __STDC_VERSION__ >= 202311L


typedef struct lite_string lite_string; ///< The \p lite_string type.

LITE_ATTR_NODISCARD LITE_ATTR_HOT lite_string *string_new(void);

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

LITE_ATTR_HOT char *string_cstr(const lite_string *restrict s);

LITE_ATTR_HOT char *string_data(const lite_string *restrict s);

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

size_t string_find_first_of_chars(const lite_string *restrict s, const char *restrict cstr);

size_t string_find_first_not_of_chars(const lite_string *restrict s, const char *restrict cstr);

size_t string_find_last_of_chars(const lite_string *restrict s, const char *restrict cstr);

size_t string_find_last_not_of_chars(const lite_string *restrict s, const char *restrict cstr);

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

long long string_to_ll(const lite_string *restrict s);

unsigned long long string_to_ull(const lite_string *restrict s);

long string_to_l(const lite_string *restrict s);

unsigned long string_to_ul(const lite_string *restrict s);

int string_to_int(const lite_string *restrict s);

unsigned int string_to_uint(const lite_string *restrict s);

double string_to_double(const lite_string *restrict s);

float string_to_float(const lite_string *restrict s);

long double string_to_ldouble(const lite_string *restrict s);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_l(long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ll(long long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ul(unsigned long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ull(unsigned long long value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_int(int value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_uint(unsigned int value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_double(double value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_float(float value);

LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ldouble(long double value);

#if defined(__cplusplus) && __cplusplus
}
#endif
