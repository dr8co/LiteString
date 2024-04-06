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
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/**
 * @brief A simple emulation of a C++ string in C.
 *
 * The data is stored as a pointer to a dynamically allocated array of characters.\n
 * The capacity represents the total number of characters that the string can hold without needing to be resized.\n
 * When the size reaches the capacity, the string is resized to a larger capacity to accommodate more characters.
 */
struct lite_str {
    char *data;      ///< A pointer to the character data.
    size_t size;     ///< The number of characters in the string, not including the null character.
    size_t capacity; ///< The total number of characters that the string can hold.
};

typedef struct lite_str lite_string;


/* /////////////////////////////////////////////////////////////////////////////
 *                             FUNCTION PROTOTYPES
 * /////////////////////////////////////////////////////////////////////////////
 */

inline lite_string *string_new();

inline void string_free(lite_string *restrict s);

inline bool string_reserve(lite_string *restrict s, size_t size);

inline bool string_push_back(lite_string *restrict s, char c);

inline char string_at(const lite_string *restrict s, size_t index);

inline void string_pop_back(lite_string *restrict s);

inline bool string_empty(const lite_string *restrict s);

inline bool string_erase(lite_string *restrict s, size_t index);

inline char string_back(const lite_string *restrict s);

inline char string_front(const lite_string *restrict s);

inline bool string_compare(const lite_string *restrict s1, const lite_string *restrict s2);

inline size_t string_length(const lite_string *restrict s);

inline size_t string_capacity(const lite_string *restrict s);

inline void string_clear(lite_string *restrict s);

inline bool string_insert(lite_string *restrict s, size_t index, char c);

inline void string_set(const lite_string *restrict s, size_t index, char c);

inline lite_string *string_substr(const lite_string *restrict s, size_t start, size_t len);

inline lite_string *string_concat(const lite_string *restrict s1, const lite_string *restrict s2);

inline bool string_append_range(lite_string *restrict s1, const lite_string *restrict s2, size_t count);

inline bool string_append(lite_string *restrict s1, const lite_string *restrict s2);

inline bool string_append_cstr(lite_string *restrict s, const char *restrict cstr);

inline char *string_cstr(const lite_string *restrict s);

inline bool string_compare_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_insert_cstr(lite_string *restrict s, const char *restrict cstr, size_t index);

inline bool string_append_cstr_range(lite_string *restrict s, const char *restrict cstr, size_t count);

inline bool string_copy_buffer(const lite_string *restrict s, char *buf);

inline bool string_copy(const lite_string *restrict src, lite_string *restrict dest);

inline bool string_case_compare(const lite_string *restrict s1, const lite_string *restrict s2);

inline bool string_case_compare_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_swap(lite_string *restrict s1, lite_string *restrict s2);

inline bool string_insert_cstr_range(lite_string *restrict s, const char *restrict cstr, size_t index, size_t count);

inline bool string_insert_range(lite_string *restrict s, const lite_string *restrict sub, size_t index, size_t count);

inline bool string_insert_string(lite_string *restrict s, const lite_string *restrict sub, size_t index);

inline size_t string_find_last_of(const lite_string *restrict s, char c);

inline size_t string_find_last_not_of(const lite_string *restrict s, char c);

inline size_t string_find_first_from(const lite_string *restrict s, char c, size_t start);

inline size_t string_find_first_of(const lite_string *restrict s, char c);

inline size_t string_find_first_not_of(const lite_string *restrict s, char c);

inline size_t string_find_substr_from(const lite_string *restrict s, const lite_string *restrict sub, size_t start);

inline size_t string_find_substr(const lite_string *restrict s, const lite_string *restrict sub);

inline size_t string_rfind_substr(const lite_string *restrict s, const lite_string *restrict sub);

inline size_t string_find_substr_cstr_from(const lite_string *restrict s, const char *restrict cstr, size_t start);

inline size_t string_rfind_substr_cstr(const lite_string *restrict s, const char *restrict cstr);

inline size_t string_find_substr_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_contains_char(const lite_string *restrict s, char c);

inline bool string_contains(const lite_string *restrict s, const lite_string *restrict sub);

inline bool string_contains_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_starts_with(const lite_string *restrict s, const lite_string *restrict sub);

inline bool string_starts_with_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_ends_with(const lite_string *restrict s, const lite_string *restrict sub);

inline bool string_ends_with_cstr(const lite_string *restrict s, const char *restrict cstr);

inline bool string_shrink(lite_string *restrict s, size_t size);

inline bool string_shrink_to_fit(lite_string *restrict s);

/* /////////////////////////////////////////////////////////////////////////////
 *                             FUNCTION DEFINITIONS
 * /////////////////////////////////////////////////////////////////////////////
 */

/**
 * @brief Creates a new string with an initial capacity of 16.
 *
 * @return A pointer to the newly created string, or NULL if memory allocation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free
 */
inline lite_string *string_new() {
    lite_string *s = (lite_string *) malloc(sizeof(lite_string));
    if (s) {
        if ((s->data = (char *) calloc(16, sizeof(char)))) {
            s->size = 0;
            s->capacity = 16;
            return s;
        }
        // If memory allocation failed, free the string
        free(s);
    }
    return nullptr;
}

/**
 * @brief Frees the memory used by a string.
 *
 * If the input pointer is NULL, the function does nothing.
 *
 * @param s A pointer to the string to be freed.
 */
inline void string_free(lite_string *const restrict s) {
    if (s) {
        if (s->data) {
            free(s->data);
            s->data = nullptr;
        }
        s->size = 0;
        s->capacity = 0;

        free(s);
    }
}

/**
 * @brief Computes the smallest power of 2 greater than or equal to the input integer.
 *
 * @param x The input integer.
 * @return The smallest power of 2 greater than or equal to the input integer.
 */
__attribute_pure__ static size_t clp2(size_t x) {
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    return ++x;
}

/**
 * @brief Resizes the string to the given size.
 *
 * @param s A pointer to the string to be resized.
 * @param size The new size for the string.
 * @return False if resizing was necessary but failed, or if the string is invalid. True otherwise.
 *
 * @note This function only resizes the string if it needs to be resized.\n
 * Resizing is needed if the new size is greater than the current capacity
 * (which should be greater than 16).\n
 * The new size is rounded up to the next power of 2 to improve performance.
 * @warning This function is for internal use only, and should not be called directly by the user.
 */
inline bool string_reserve(lite_string *const restrict s, size_t size) {
    if (s) {
        if (size <= 16) return true;

        // Round up the new size to the next power of 2, and reallocate the memory if necessary
        size = clp2(size);
        if (size >= s->capacity) {
            void *temp = realloc(s->data, size * sizeof(char));
            if (temp == nullptr) return false;

            // Update the string's data pointer
            s->data = (char *) temp;
            // Set the new capacity to the new size, and initialize the new memory to zero
            s->capacity = size;
            memset(s->data + s->size, '\0', s->capacity - s->size);
        }
        return true;
    }

    return false;
}

/**
 * @brief Inserts a specified number of characters from a C-string into a string at a specified index.
 *
 * @param s A pointer to the string where the characters will be inserted.
 * @param cstr The C-string from which the characters will be copied.
 * @param index The index at which the characters will be inserted.
 * @param count The number of characters to be copied from the C-string to the string.
 * @return true if the characters were successfully inserted, false otherwise.
 *
 * @note If the index is equal to the size of the string and the string is empty,
 * the function will append the characters from the C-string to the string.
 */
inline bool string_insert_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t index,
                              const size_t count) {
    if (s && cstr) {
        if (!count) return true;
        if (count <= strlen(cstr)) {
            // The index must be within the bounds of the string
            if (index < s->size) {
                // Resize the string if necessary
                if (s->size + count >= s->capacity) {
                    if (!string_reserve(s, s->size + count)) return false;
                }
                // Move the characters after the index to make room for the C-string
                memmove(s->data + (index + count) * sizeof(char), s->data + index * sizeof(char),
                        (s->size - index) * sizeof(char));

                // Copy the C-string into the string
                memcpy(s->data + index * sizeof(char), cstr, count * sizeof(char));
                s->size += count;

                return true;
            }
            if (index == s->size) return string_append_cstr_range(s, cstr, count);
        }
    }
    return false;
}

/**
 * @brief Inserts a C-string into a string at a specified index.
 *
 * @param s A pointer to the string where the C-string will be inserted.
 * @param index The index at which the C-string will be inserted.
 * @param cstr The C-string to be inserted.
 * @return true if the C-string was successfully inserted, false otherwise.
 */
inline bool string_insert_cstr(lite_string *const restrict s, const char *restrict cstr, const size_t index) {
    return cstr && string_insert_cstr_range(s, cstr, index, strlen(cstr));
}


/**
 * @brief Appends a character to the end of a string.
 *
 * @param s A pointer to the string where the character will be appended.
 * @param c The character to be appended.
 * @return true if the character was successfully appended, false otherwise.
 *
 * @note If the string is full, it is resized to twice its current capacity.\n
 * The character is not appended if it is the null character.
 */
inline bool string_push_back(lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        if (s->size == s->capacity) {
            if (!string_reserve(s, s->capacity * 2)) return false;
        }
        s->data[s->size++] = c;
        return true;
    }
    return false;
}

/**
 * @brief Retrieves the character at a given index in the string.
 *
 * @param s A pointer to the string.
 * @param index The index of the character to be retrieved.
 * @return The character at the given index, or the null character if the index is out of bounds or the string is invalid.
 */
char string_at(const lite_string *const restrict s, const size_t index) {
    if (s && index < s->size)
        return s->data[index];

    return '\0';
}

/**
 * @brief Removes the last character from the string.
 *
 * If the string is valid and not empty, it replaces replaces the last character with the null character.
 *
 * @param s A pointer to the string.
 */
inline void string_pop_back(lite_string *const restrict s) {
    if (s && s->size)
        s->data[--s->size] = '\0';
}

/**
 * @brief Checks if the string is empty.
 *
 * @param s A pointer to the string.
 * @return true if the string is empty or invalid, false otherwise.
 */
inline bool string_empty(const lite_string *const restrict s) {
    return s == nullptr || s->size == 0;
}

/**
 * @brief Retrieves the last character of a string.
 *
 * @param s A pointer to the string.
 * @return The last character of the string if the string is valid and not empty, or the null character otherwise.
 */
inline char string_back(const lite_string *const restrict s) {
    return s && s->size ? s->data[s->size - 1] : '\0';
}

/**
 * @brief Retrieves the first character of a string.
 *
 * @param s A pointer to the string.
 * @return The first character of the string if the string is valid and not empty, or the null character otherwise.
 */
inline char string_front(const lite_string *const restrict s) {
    return s && s->size ? s->data[0] : '\0';
}

/**
 * @brief Removes the character at a given index in the string.
 *
 * @param s A pointer to the string.
 * @param index The index of the character to be removed.
 * @return true if the character was successfully removed, false otherwise.
 */
inline bool string_erase(lite_string *const restrict s, const size_t index) {
    if (s && index < s->size) {
        // Move the characters after the index to overwrite the character to be removed
        memmove(s->data + index * sizeof(char), s->data + (index + 1) * sizeof(char), (s->size - index) * sizeof(char));
        // Replace the last character with the null character
        s->data[--s->size] = '\0';
        return true;
    }
    return false;
}

/**
 * @brief Compares two strings for equality.
 *
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @return true if the strings are equal, false otherwise.
 */
inline bool string_compare(const lite_string *const restrict s1, const lite_string *const restrict s2) {
    if (s1 == nullptr || s2 == nullptr || s1->size != s2->size)
        return false;

    return memcmp(s1->data, s2->data, s1->size) == 0;
}

/**
 * @brief Compares two strings for equality, ignoring case.
 *
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @return true if the strings are equal (ignoring case), false otherwise.
 */
inline bool string_case_compare(const lite_string *const restrict s1, const lite_string *const restrict s2) {
    if (s1 == nullptr || s2 == nullptr || s1->size != s2->size)
        return false;

    return strncasecmp(s1->data, s2->data, s1->size) == 0;
}

/**
 * @brief Returns the length of the string.
 *
 * @param s A pointer to the string.
 * @return The length of the string, or 0 if the string is invalid.
 */
inline size_t string_length(const lite_string *const restrict s) {
    return s ? s->size : 0;
}

/**
 * @brief Returns the capacity of the string.
 *
 * @param s A pointer to the string.
 * @return The capacity of the string, or 0 if the string is invalid.
 */
inline size_t string_capacity(const lite_string *const restrict s) {
    return s ? s->capacity : 0;
}

/**
 * @brief Clears the string.
 *
 * @param s A pointer to the string.
 */
inline void string_clear(lite_string *const restrict s) {
    if (s && s->size) {
        memset(s->data, '\0', s->size);
        s->size = 0;
    }
}

/**
 * @brief Inserts a new character at a given index in the string.
 *
 * @param s A pointer to the string where the character will be inserted.
 * @param index The index at which the character will be inserted.
 * @param c The character to be inserted.
 * @return true if the character was successfully inserted, false otherwise.
 */
inline bool string_insert(lite_string *const restrict s, const size_t index, const char c) {
    if (s && c != '\0') {
        if (index < s->size) {
            // Resize the string if necessary
            if (s->size == s->capacity) {
                if (!string_reserve(s, s->capacity * 2)) return false;
            }
            // Move the characters after the index to make room for the new character
            memmove(s->data + (index + 1) * sizeof(char), s->data + index * sizeof(char),
                    (s->size - index) * sizeof(char));

            // Insert the new character into the string
            s->data[index] = c;
            ++s->size;

            return true;
        }
        if (index == 0 && s->size == 0) return string_push_back(s, c);
    }
    return false;
}

/**
 * @brief Inserts a specified number of characters from a substring into a string at a specified index.
 *
 * @param s A pointer to the string where the characters will be inserted.
 * @param sub A pointer to the substring from which the characters will be copied.
 * @param index The index at which the characters will be inserted.
 * @param count The number of characters to be copied from the substring to the string.
 * @return true if the characters were successfully inserted, false otherwise.
 *
 * @note If the index is equal to the size of the string and the string is empty,
 * the function will append the characters from the substring to the string.
 */
inline bool string_insert_range(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index,
                         const size_t count) {
    if (s && sub) {
        if (!count) return true;
        if (count <= sub->size) {
            if (index < s->size) {
                if (s->size + count >= s->capacity) {
                    if (!string_reserve(s, s->size + count)) return false;
                }
                memmove(s->data + (index + count) * sizeof(char), s->data + index * sizeof(char),
                        (s->size - index) * sizeof(char));

                memcpy(s->data + index * sizeof(char), sub->data, count * sizeof(char));
                s->size += count;

                return true;
            }
            if (index == 0 && s->size == 0) return string_append_range(s, sub, count);
        }
    }
    return false;
}

/**
 * @brief Modifies the character at a given index in the string.
 *
 * @param s A pointer to the string where the character will be modified.
 * @param index The index of the character to be modified.
 * @param c The new character.
 */
inline void string_set(const lite_string *const restrict s, const size_t index, const char c) {
    if (s && c != '\0' && index < s->size)
        s->data[index] = c;
}

inline bool string_insert_string(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index) {
    return sub && string_insert_range(s, sub, index, sub->size);
}

/**
 * @brief Retrieves a substring from the string.
 *
 * @param s A pointer to the string from which the substring will be retrieved.
 * @param start The start index of the substring.
 * @param len The length of the substring.
 * @return A pointer to the new string containing the substring, or NULL if the substring could not be retrieved.
 *
 * @note The returned pointer must be freed by the caller, using \p string_free
 */
inline lite_string *string_substr(const lite_string *const restrict s, const size_t start, const size_t len) {
    if (s) {
        // The requested substring must be within the bounds of the string
        if (len == 0 || start + len - 1 > s->size) return nullptr;

        // Create a new string to store the substring
        lite_string *sub = string_new();
        if (sub) {
            // Resize the new string to the length of the substring
            if (string_reserve(sub, len)) {
                // Copy the substring into the new string
                memcpy(sub->data, s->data + start, len);
                sub->size = len;
                return sub;
            }
            // If resizing failed, free the new string
            string_free(sub);
        }
    }
    return nullptr;
}

/**
 * @brief Concatenates two strings.
 *
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @return A pointer to the new string containing the concatenated strings,
 * or NULL if the strings could not be concatenated.
 * @note The returned pointer must be freed by the caller, using \p string_free
 */
inline lite_string *string_concat(const lite_string *const restrict s1, const lite_string *const restrict s2) {
    if (s1 && s2) {
        lite_string *s = string_new();
        if (s) {
            // Resize the new string appropriately
            if (string_reserve(s, s1->size + s2->size)) {
                // Copy the input strings into the new string
                memcpy(s->data, s1->data, s1->size * sizeof(char));
                memcpy(s->data + s1->size * sizeof(char), s2->data, s2->size * sizeof(char));

                s->size = s1->size + s2->size;

                return s;
            }
            // If resizing failed, free the new string
            string_free(s);
        }
    }
    return nullptr;
}

/**
 * @brief Appends a specified number of characters from one string to another.
 *
 * @param s1 A pointer to the string where the characters will be appended.
 * @param s2 A pointer to the string from which the characters will be copied.
 * @param count The number of characters to be copied from the second string to the first string.
 * @return true if the characters were successfully appended, false otherwise.
 */
inline bool string_append_range(lite_string *const restrict s1, const lite_string *const restrict s2, const size_t count) {
    if (s1) {
        if (count == 0) return true;

        if (s2) {
            if (count <= s2->size) {
                if (string_reserve(s1, s1->size + count)) {
                    // Copy the characters from the second string into the first string
                    memcpy(s1->data + s1->size * sizeof(char), s2->data, count * sizeof(char));

                    s1->size += count;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Appends a string to the end of another string.
 *
 * @param s1 A pointer to the string where the second string will be appended.
 * @param s2 A pointer to the string that will be appended to the first string.
 * @return true if the second string was successfully appended, false otherwise.
 */
inline bool string_append(lite_string *const restrict s1, const lite_string *const restrict s2) {
    return s2 && string_append_range(s1, s2, s2->size);
}

/**
 * @brief Appends a specified number of characters from a C-string to a string.
 *
 * @param s A pointer to the string where the characters will be appended.
 * @param cstr The C-string from which the characters will be copied.
 * @param count The number of characters to be copied from the C-string to the string.
 * @return true if the characters were successfully appended, false otherwise.
 */
inline bool string_append_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t count) {
    if (s) {
        if (count == 0) return true;
        if (cstr) {
            // Resize the string if necessary
            if (count <= strlen(cstr)) {
                if (string_reserve(s, s->size + count)) {
                    // Copy the C-string into the string
                    memcpy(s->data + s->size * sizeof(char), cstr, count * sizeof(char));
                    s->size += count;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * @brief Appends a C-string to the end of a string.
 *
 * @param s A pointer to the string where the C-string will be appended.
 * @param cstr The C-string to be appended to the string.
 * @return true if the C-string was successfully appended, false otherwise.
 */
inline bool string_append_cstr(lite_string *const restrict s, const char *const restrict cstr) {
    return string_append_cstr_range(s, cstr, strlen(cstr));
}

/**
 * @brief Converts a string to a C-string.
 *
 * @param s A pointer to the string to be converted.
 * @return A pointer to the newly created C-string, or NULL if the string could not be converted.
 * @note The returned C-string must be freed by the caller.\n
 * It is better to use \p string_copy_buffer if the C-string is only needed temporarily.
 */
inline char *string_cstr(const lite_string *const restrict s) {
    if (s) {
        // Allocate memory for the C-string
        char *cstr = (char *) malloc((s->size + 1) * sizeof(char));
        if (cstr) {
            // Copy the characters from the string to the C-string
            memcpy(cstr, s->data, s->size);

            // Append the null character to the end of the C-string
            cstr[s->size] = '\0';
            return cstr;
        }
    }
    return nullptr;
}

/**
 * @brief Compares a string with a C-string for equality.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be compared with the string.
 * @return true if the string and the C-string are equal, false otherwise.
 */
inline bool string_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    if (s && cstr) {
        if (s->size == strlen(cstr))
            return memcmp(s->data, cstr, s->size) == 0;
    }
    return false;
}

/**
 * @brief Compares a string with a C-string for equality, ignoring case.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be compared with the string.
 * @return true if the string and the C-string are equal (ignoring case), false otherwise.
 */
inline bool string_case_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    if (s && cstr) {
        if (s->size == strlen(cstr))
            return strncasecmp(s->data, cstr, s->size) == 0;
    }
    return false;
}

/**
 * @brief Copies the characters from a string to a buffer.
 *
 * @param s A pointer to the string.
 * @param buf The buffer where the characters will be copied.
 * @return true if the characters were successfully copied, false otherwise.
 */
inline bool string_copy_buffer(const lite_string *const restrict s, char *buf) {
    if (s && !string_empty(s)) {
        // Copy the characters from the string to the buffer
        memcpy(buf, s->data, s->size * sizeof(char));
        // Append the null character to the end of the buffer
        buf[s->size] = '\0';
        return true;
    }
    return false;
}

/**
 * @brief Copies the contents of one string to another.
 *
 * @param src A pointer to the source string.
 * @param dest A pointer to the destination string.
 * @return true if the contents of the source string were successfully copied to the destination string, false otherwise.
 */
inline bool string_copy(const lite_string *const restrict src, lite_string *const restrict dest) {
    if (src && dest && src->data && dest->data) {
        // Resize the destination string if necessary
        if (src->size > dest->size)
            if (!string_reserve(dest, src->size)) return false;

        // Copy the characters from the source string to the destination string
        memcpy(dest->data, src->data, src->size * sizeof(char));
        dest->size = src->size;
        return true;
    }
    return false;
}

/**
 * @brief Swaps the contents of two strings.
 *
 * @param s1 A pointer to the first string.
 * @param s2 A pointer to the second string.
 * @return true if the contents of the strings were successfully swapped, false otherwise.
 */
inline bool string_swap(lite_string *const restrict s1, lite_string *const restrict s2) {
    if (s1 && s2) {
        const lite_string temp = *s1;
        *s1 = *s2;
        *s2 = temp;

        return true;
    }
    return false;
}

/**
 * @brief Finds the last occurrence of a character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @return The index of the last occurrence of the character in the string, or \p SIZE_MAX if the character was not found.
 */
inline size_t string_find_last_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        for (size_t i = s->size; i > 0; --i) {
            if (s->data[i - 1] == c)
                return i - 1;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the last occurrence of a character that does not match the specified character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be compared against.
 * @return The index of the last occurrence of a character that does not match the specified character in the string,
 * or \p SIZE_MAX if all characters match or the string is invalid.
 */
inline size_t string_find_last_not_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        for (size_t i = s->size; i > 0; --i) {
            if (s->data[i - 1] != c)
                return i - 1;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a character in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the character in the string, or \p SIZE_MAX if the character was not found.
 */
inline size_t string_find_first_from(const lite_string *const restrict s, const char c, const size_t start) {
    if (s && c != '\0' && start < s->size) {
        for (size_t i = start; i < s->size; ++i) {
            if (s->data[i] == c)
                return i;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @return The index of the first occurrence of the character in the string, or \p SIZE_MAX if the character was not found.
 */
inline size_t string_find_first_of(const lite_string *const restrict s, const char c) {
    return string_find_first_from(s, c, 0);
}

/**
 * @brief Finds the first occurrence of a character that does not match the specified character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be compared against.
 * @return The index of the first occurrence of a character that does not match the specified character in the string,
 * or \p SIZE_MAX if all characters match or the string is invalid.
 */
inline size_t string_find_first_not_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        for (size_t i = 0; i < s->size; ++i) {
            if (s->data[i] != c)
                return i;
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Checks if a string contains a specified character.
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @return True if the string contains the character, false otherwise.
 */
inline bool string_contains_char(const lite_string *const restrict s, const char c) {
    return string_find_first_of(s, c) != SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a substring in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the substring in the string, or \p SIZE_MAX if the substring was not found.
 */
inline size_t string_find_substr_from(const lite_string *const restrict s, const lite_string *const restrict sub,
                               const size_t start) {
    if (s && sub && start < s->size) {
        if (sub->size == 0) return start;
        if (sub->size > s->size) return SIZE_MAX;

        for (size_t i = start; i < s->size - sub->size + 1; ++i) {
            if (s->data[i] == sub->data[0]) {
                bool found = true;
                for (size_t j = 1; j < sub->size; ++j) {
                    if (s->data[i + j] != sub->data[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) return i;
            }
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a substring in a string.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return The index of the first occurrence of the substring in the string, or \p SIZE_MAX if the substring was not found.
 */
inline size_t string_find_substr(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find_substr_from(s, sub, 0);
}

/**
 * @brief Finds the last occurrence of a substring in a string.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return The index of the last occurrence of the substring in the string, or \p SIZE_MAX if the substring was not found.
 */
inline size_t string_rfind_substr(const lite_string *const restrict s, const lite_string *const restrict sub) {
    if (s && sub) {
        if (sub->size == 0) return s->size;
        if (sub->size > s->size) return SIZE_MAX;

        for (size_t i = s->size - sub->size; i > 0; --i) {
            if (s->data[i] == sub->data[0]) {
                bool found = true;
                for (size_t j = 1; j < sub->size; ++j) {
                    if (s->data[i + j] != sub->data[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) return i;
            }
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a C-string in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the C-string in the string, or \p SIZE_MAX if the C-string was not found.
 */
inline size_t string_find_substr_cstr_from(const lite_string *const restrict s, const char *const restrict cstr,
                                    const size_t start) {
    if (s && cstr && start < s->size) {
        const size_t len = strlen(cstr);
        if (len == 0) return start;
        if (len > s->size) return SIZE_MAX;

        for (size_t i = start; i < s->size - len + 1; ++i) {
            if (s->data[i] == cstr[0]) {
                bool found = true;
                for (size_t j = 1; j < len; ++j) {
                    if (s->data[i + j] != cstr[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) return i;
            }
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the last occurrence of a C-string in a string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return The index of the last occurrence of the C-string in the string, or \p SIZE_MAX if the C-string was not found.
 */
inline size_t string_rfind_substr_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    if (s && cstr) {
        const size_t len = strlen(cstr);
        if (len == 0) return s->size;
        if (len > s->size) return SIZE_MAX;

        for (size_t i = s->size - len; i > 0; --i) {
            if (s->data[i] == cstr[0]) {
                bool found = true;
                for (size_t j = 1; j < len; ++j) {
                    if (s->data[i + j] != cstr[j]) {
                        found = false;
                        break;
                    }
                }
                if (found) return i;
            }
        }
    }
    return SIZE_MAX;
}

/**
 * @brief Finds the first occurrence of a C-string in a string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return The index of the first occurrence of the C-string in the string, or \p SIZE_MAX if the C-string was not found.
 */
inline size_t string_find_substr_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_substr_cstr_from(s, cstr, 0);
}

/**
 * @brief Checks if a string contains a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return True if the string contains the substring, false otherwise.
 */
inline bool string_contains(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find_substr(s, sub) != SIZE_MAX;
}

/**
 * @brief Checks if a string contains a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return True if the string contains the C-string, false otherwise.
 */
inline bool string_contains_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_substr_cstr(s, cstr) != SIZE_MAX;
}

/**
 * @brief Checks if a string starts with a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be checked.
 * @return True if the string starts with the substring, false otherwise.
 */
inline bool string_starts_with(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find_substr(s, sub) == 0;
}

/**
 * @brief Checks if a string starts with a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be checked.
 * @return True if the string starts with the C-string, false otherwise.
 */
inline bool string_starts_with_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_substr_cstr(s, cstr) == 0;
}

/**
 * @brief Checks if a string ends with a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be checked.
 * @return True if the string ends with the substring, false otherwise.
 */
inline bool string_ends_with(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return s && sub && string_rfind_substr(s, sub) == s->size - sub->size;
}

/**
 * @brief Checks if a string ends with a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be checked.
 * @return True if the string ends with the C-string, false otherwise.
 */
inline bool string_ends_with_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return s && cstr && string_rfind_substr_cstr(s, cstr) == s->size - strlen(cstr);
}


/**
 * @brief Shrinks the string to a specified size.
 *
 * @param s A pointer to the string to be shrunk.
 * @param size The new size for the string.
 * @return true if the string was successfully shrunk, false otherwise.
 *
 * @note Extra characters are removed from the end of the string.
 */
inline bool string_shrink(lite_string *const restrict s, const size_t size) {
    if (s && size < s->size) {
        s->size = size;
        s->data[size] = '\0';
        return true;
    }
    return false;
}

/**
 * @brief Shrinks the string to fit its size.
 *
 * @param s A pointer to the string to be shrunk.
 * @return true if the string was successfully shrunk or if shrinking was unnecessary, false otherwise.
 */
inline bool string_shrink_to_fit(lite_string *const restrict s) {
    if (s) {
        // If the string is empty, or if the size is equal to the capacity, no resizing is necessary
        if (!s->size || s->size == s->capacity) return true;

        char *temp = (char *) realloc(s->data, s->size * sizeof(char));
        if (temp) {
            s->data = temp;
            s->capacity = s->size;
            return true;
        }
    }
    return false;
}

#if __cplusplus
}
#endif
