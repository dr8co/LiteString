#include <stdlib.h>
#include <string.h>
#include "lite_string.h"
#include <stdio.h>

#if __has_c_attribute(gnu::always_inline)
#define LITE_ATTR_ALWAYS_INLINE [[gnu::always_inline]]
#else
#define LITE_ATTR_ALWAYS_INLINE
#endif


/**
 * @brief Creates a new string with an initial capacity of 16.
 *
 * @return A pointer to the newly created string, or NULL if memory allocation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free
 */
LITE_ATTR_NODISCARD LITE_ATTR_HOT lite_string *string_new() {
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
 * @brief Creates a new string and initializes it with a C-string.
 *
 * @param cstr A pointer to the C-string that will be used to initialize the new string.
 * @return A pointer to the newly created string, or NULL if the memory allocation failed or the C-string is NULL.
 * @note The returned pointer must be freed by the caller, using the \p string_free() function.
 */
LITE_ATTR_NODISCARD LITE_ATTR_HOT lite_string *string_new_cstr(const char *const restrict cstr) {
    lite_string *s = string_new();
    if (cstr && s) {
        if (!string_append_cstr(s, cstr)) {
            string_free(s);
            return nullptr;
        }
    }
    return s;
}

/**
 * @brief Frees the memory used by a string.
 *
 * If the input pointer is NULL, the function does nothing.
 *
 * @param s A pointer to the string to be freed.
 */
LITE_ATTR_HOT void string_free(lite_string *const restrict s) {
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
 *
 * @note This function is for internal use only, and should not be called directly by the user.
 */
LITE_ATTR_UNSEQUENCED LITE_ATTR_ALWAYS_INLINE static inline size_t lite_clp2_(size_t x) {
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
LITE_ATTR_HOT bool string_reserve(lite_string *const restrict s, size_t size) {
    if (s) {
        // Space for the null terminator
        ++size;

        // Round up the new size to the next power of 2
        size = lite_clp2_(size);
        if (size < 16) size = 16;

        // Reallocate the memory
        if (size > s->capacity - 1) {
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
bool string_insert_cstr_range(lite_string *const restrict s, const char *const restrict cstr,
                              const size_t index, const size_t count) {
    if (s && cstr) {
        if (!count) return true;
        if (count <= strlen(cstr)) {
            // The index must be within the bounds of the string
            if (index < s->size) {
                // Resize the string if necessary
                if (s->size + count >= s->capacity - 1) {
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
bool string_insert_cstr(lite_string *const restrict s, const char *restrict cstr, const size_t index) {
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
bool string_push_back(lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        if (s->size >= s->capacity - 1) {
            if (!string_reserve(s, s->capacity << 1)) return false;
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
void string_pop_back(lite_string *const restrict s) {
    if (s && s->size)
        s->data[--s->size] = '\0';
}

/**
 * @brief Checks if the string is empty.
 *
 * @param s A pointer to the string.
 * @return true if the string is empty or invalid, false otherwise.
 */
bool string_empty(const lite_string *const restrict s) {
    return s == nullptr || s->size == 0;
}

/**
 * @brief Retrieves the last character of a string.
 *
 * @param s A pointer to the string.
 * @return The last character of the string if the string is valid and not empty, or the null character otherwise.
 */
char string_back(const lite_string *const restrict s) {
    return s && s->size ? s->data[s->size - 1] : '\0';
}

/**
 * @brief Retrieves the first character of a string.
 *
 * @param s A pointer to the string.
 * @return The first character of the string if the string is valid and not empty, or the null character otherwise.
 */
char string_front(const lite_string *const restrict s) {
    return s && s->size ? s->data[0] : '\0';
}

/**
 * @brief Erases a range of characters from a string.
 *
 * @param s A pointer to the string from which the characters will be removed.
 * @param start The starting index of the range to be removed.
 * @param count The number of characters to be removed.
 * @return true if the characters were successfully removed, false otherwise.
 */
bool string_erase_range(lite_string *const restrict s, const size_t start, const size_t count) {
    if (s && start < s->size) {
        if (count == 0) return true;
#if (__GNUC__ || __clang__) && __has_builtin(__builtin_add_overflow)
        size_t end;
        if (!__builtin_uaddl_overflow(start, count, &end) && end <= s->size)
#else
        if (count < s->size && start + count <= s->size)
#endif
        {
            // Copy the characters after the range to overwrite the characters to be removed
            memmove(s->data + start * sizeof(char), s->data + (start + count) * sizeof(char),
                    (s->size - start - count) * sizeof(char));
            s->size -= count;

            // Fill the remaining space with null characters
            memset(s->data + s->size, '\0', s->capacity - s->size);
            return true;
        }
    }
    return false;
}


/**
 * @brief Removes the character at a given index in the string.
 *
 * @param s A pointer to the string.
 * @param index The index of the character to be removed.
 * @return true if the character was successfully removed, false otherwise.
 */
bool string_erase(lite_string *const restrict s, const size_t index) {
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
bool string_compare(const lite_string *const restrict s1, const lite_string *const restrict s2) {
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
bool string_case_compare(const lite_string *const restrict s1, const lite_string *const restrict s2) {
    if (s1 == nullptr || s2 == nullptr || s1->size != s2->size)
        return false;

    return strncasecmp(s1->data, s2->data, s1->size) == 0;
}

/**
 * @brief Returns the length of a string.
 *
 * @param s A pointer to the string.
 * @return The length of the string, or 0 if the string is invalid.
 */
LITE_ATTR_HOT size_t string_length(const lite_string *const restrict s) {
    return s ? s->size : 0;
}

/**
 * @brief Returns the size of a string.
 *
 * @param s A pointer to the string.
 * @return The length of the string, or 0 if the string is invalid.
 */
LITE_ATTR_HOT size_t string_size(const lite_string *const restrict s) {
    return string_length(s);
}

/**
 * @brief Returns the capacity of the string.
 *
 * @param s A pointer to the string.
 * @return The capacity of the string, or 0 if the string is invalid.
 */
size_t string_capacity(const lite_string *const restrict s) {
    return s ? s->capacity : 0;
}

/**
 * @brief Clears the string.
 *
 * @param s A pointer to the string.
 */
void string_clear(lite_string *const restrict s) {
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
bool string_insert(lite_string *const restrict s, const size_t index, const char c) {
    if (s && c != '\0') {
        if (index < s->size) {
            // Resize the string if necessary
            if (s->size >= s->capacity - 1) {
                if (!string_reserve(s, s->capacity << 1)) return false;
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
bool
string_insert_range(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index,
                    const size_t count) {
    if (s && sub) {
        if (!count) return true;
        if (count <= sub->size) {
            if (index < s->size) {
                if (s->size + count >= s->capacity - 1) {
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
void string_set(const lite_string *const restrict s, const size_t index, const char c) {
    if (s && c != '\0' && index < s->size)
        s->data[index] = c;
}

bool
string_insert_string(lite_string *const restrict s, const lite_string *const restrict sub, const size_t index) {
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
LITE_ATTR_NODISCARD lite_string *string_substr(const lite_string *const restrict s, const size_t start,
                                               const size_t len) {
    if (s) {
        // The requested substring must be within the bounds of the string
        if (len == 0 || start >= s->size || len > s->size || start + len - 1 > s->size) return nullptr;

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
LITE_ATTR_NODISCARD lite_string *string_concat(const lite_string *const restrict s1,
                                               const lite_string *const restrict s2) {
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
bool
string_append_range(lite_string *const restrict s1, const lite_string *const restrict s2, const size_t count) {
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
bool string_append(lite_string *const restrict s1, const lite_string *const restrict s2) {
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
bool
string_append_cstr_range(lite_string *const restrict s, const char *const restrict cstr, const size_t count) {
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
bool string_append_cstr(lite_string *const restrict s, const char *const restrict cstr) {
    return string_append_cstr_range(s, cstr, strlen(cstr));
}

/**
 * @brief Returns a pointer to the C-string representation of a string.
 *
 * @param s A pointer to the string.
 * @return A pointer to the C-string representation of the string, or NULL if the string is invalid.
 * @note It is not recommended to modify the string's data directly. Use the provided functions instead.
 */
LITE_ATTR_HOT char *string_cstr(const lite_string *const restrict s) {
    if (s) {
        // Check if the string is null-terminated
        if (s->data[s->size] != '\0')
            s->data[s->size] = '\0';

        return s->data;
    }
    return nullptr;
}

/**
 * @brief Returns a pointer to the underlying character array holding the string data.
 *
 * @param s A pointer to the string.
 * @return A pointer to the string's data, or a null pointer if the string is null.
 * @note It is not recommended to modify the string's data directly. Use the provided functions instead.
 * @note The returned pointer is not guaranteed to be null-terminated.
 * Use \p string_cstr() to get a null-terminated C-string.
 */
LITE_ATTR_HOT char *string_data(const lite_string *const restrict s) {
    return s ? s->data : nullptr;
}

/**
 * @brief Compares a string with a C-string for equality.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be compared with the string.
 * @return true if the string and the C-string are equal, false otherwise.
 */
bool string_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
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
bool string_case_compare_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
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
bool string_copy_buffer(const lite_string *const restrict s, char *buf) {
    if (s && buf && !string_empty(s)) {
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
bool string_copy(const lite_string *const restrict src, lite_string *const restrict dest) {
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
bool string_swap(lite_string *const restrict s1, lite_string *const restrict s2) {
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
 * @return The index of the last occurrence of the character in the string,
 * or \p lite_string_npos if the character was not found.
 */
size_t string_find_last_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
#if _GNU_SOURCE
        const char *found = (const char *) memrchr(s->data, c, s->size);
        if (found) return found - s->data;
#else
        for (size_t i = s->size; i > 0; --i) {
            if (s->data[i - 1] == c)
                return i - 1;
        }
#endif
    }
    return lite_string_npos;
}

/**
 * @brief Finds the last occurrence of a character that does not match the specified character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be compared against.
 * @return The index of the last occurrence of a character that does not match the specified character in the string,
 * or \p lite_string_npos if all characters match or the string is invalid.
 */
size_t string_find_last_not_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        for (size_t i = s->size; i > 0; --i) {
            if (s->data[i - 1] != c)
                return i - 1;
        }
    }
    return lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a character in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the character in the string,
 * or \p lite_string_npos if the character was not found.
 */
size_t string_find_first_from(const lite_string *const restrict s, const char c, const size_t start) {
    if (s && c != '\0' && start < s->size) {
        const char *found = (const char *) memchr(s->data + start, c, s->size - start);
        if (found) return found - s->data;
    }
    return lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @return The index of the first occurrence of the character in the string,
 * or \p lite_string_npos if the character was not found.
 */
size_t string_find_first_of(const lite_string *const restrict s, const char c) {
    return string_find_first_from(s, c, 0);
}

/**
 * @brief Finds the first occurrence of a character that does not match the specified character in a string.
 *
 * @param s A pointer to the string.
 * @param c The character to be compared against.
 * @return The index of the first occurrence of a character that does not match the specified character in the string,
 * or \p lite_string_npos if all characters match or the string is invalid.
 */
size_t string_find_first_not_of(const lite_string *const restrict s, const char c) {
    if (s && c != '\0') {
        for (size_t i = 0; i < s->size; ++i) {
            if (s->data[i] != c)
                return i;
        }
    }
    return lite_string_npos;
}

/**
 * @brief Checks if a string contains a specified character.
 * @param s A pointer to the string.
 * @param c The character to be found.
 * @return True if the string contains the character, false otherwise.
 */
bool string_contains_char(const lite_string *const restrict s, const char c) {
    return string_find_first_of(s, c) != lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a substring in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the substring in the string,
 * or \p lite_string_npos if the substring was not found.
 */
size_t string_find_from(const lite_string *const restrict s, const lite_string *const restrict sub,
                        const size_t start) {
    if (s && sub && start < s->size) {
        if (sub->size == 0) return start;
        if (sub->size > s->size) return lite_string_npos;
#if _GNU_SOURCE
        const char *found = (const char *) memmem(s->data + start, s->size - start, sub->data, sub->size);
        if (found) return found - s->data;
#else
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
#endif
    }
    return lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a substring in a string.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return The index of the first occurrence of the substring in the string,
 * or \p lite_string_npos if the substring was not found.
 */
size_t string_find(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find_from(s, sub, 0);
}

/**
 * @brief Finds the last occurrence of a substring in a string.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return The index of the last occurrence of the substring in the string,
 * or \p lite_string_npos if the substring was not found.
 */
size_t string_rfind(const lite_string *const restrict s, const lite_string *const restrict sub) {
    if (s && sub) {
        if (sub->size == 0) return s->size;
        if (sub->size > s->size) return lite_string_npos;

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
    return lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a C-string in a string, starting from a specified index.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @param start The index from which the search will start.
 * @return The index of the first occurrence of the C-string in the string,
 * or \p lite_string_npos if the C-string was not found.
 */
size_t string_find_cstr_from(const lite_string *const restrict s, const char *const restrict cstr,
                             const size_t start) {
    // The string and the C-string must be valid
    if (s && cstr) {
        const size_t len = strlen(cstr);
        // Empty C-strings are always found
        if (len == 0) return start;
        // The C-string must be within the bounds of the string
        if (len > s->size) return lite_string_npos;

        // The search must start from a valid index
        if (start < s->size) {
#if _GNU_SOURCE
            const char *found = (const char *) memmem(s->data + start, s->size - start, cstr, len);
            if (found) return found - s->data;
#else
            // Search for the C-string in the string
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
#endif
    }
    // The C-string was not found
    return lite_string_npos;
}

/**
 * @brief Finds the last occurrence of a C-string in a string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return The index of the last occurrence of the C-string in the string,
 * or \p lite_string_npos if the C-string was not found.
 */
size_t string_rfind_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    if (s && cstr) {
        const size_t len = strlen(cstr);
        if (len == 0) return s->size;
        if (len > s->size) return lite_string_npos;

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
    return lite_string_npos;
}

/**
 * @brief Finds the first occurrence of a C-string in a string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return The index of the first occurrence of the C-string in the string,
 * or \p lite_string_npos if the C-string was not found.
 */
size_t string_find_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_cstr_from(s, cstr, 0);
}

/**
 * @brief Checks if a string contains a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be found.
 * @return True if the string contains the substring, false otherwise.
 */
bool string_contains(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find(s, sub) != lite_string_npos;
}

/**
 * @brief Checks if a string contains a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be found.
 * @return True if the string contains the C-string, false otherwise.
 */
bool string_contains_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_cstr(s, cstr) != lite_string_npos;
}

/**
 * @brief Checks if a string starts with a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be checked.
 * @return True if the string starts with the substring, false otherwise.
 */
bool string_starts_with(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return string_find(s, sub) == 0;
}

/**
 * @brief Checks if a string starts with a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be checked.
 * @return True if the string starts with the C-string, false otherwise.
 */
bool string_starts_with_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return string_find_cstr(s, cstr) == 0;
}

/**
 * @brief Checks if a string ends with a specified substring.
 *
 * @param s A pointer to the string.
 * @param sub A pointer to the substring to be checked.
 * @return True if the string ends with the substring, false otherwise.
 */
bool string_ends_with(const lite_string *const restrict s, const lite_string *const restrict sub) {
    return s && sub && string_rfind(s, sub) == s->size - sub->size;
}

/**
 * @brief Checks if a string ends with a specified C-string.
 *
 * @param s A pointer to the string.
 * @param cstr The C-string to be checked.
 * @return True if the string ends with the C-string, false otherwise.
 */
bool string_ends_with_cstr(const lite_string *const restrict s, const char *const restrict cstr) {
    return s && cstr && string_rfind_cstr(s, cstr) == s->size - strlen(cstr);
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
bool string_shrink(lite_string *const restrict s, const size_t size) {
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
bool string_shrink_to_fit(lite_string *const restrict s) {
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

/**
 * @brief Converts all the uppercase characters in a string to lowercase.
 *
 * @param s A pointer to the string to be converted to lowercase.
 */
void string_to_lower(const lite_string *const restrict s) {
    if (s) {
        for (size_t i = 0; i < s->size; ++i) {
            if (s->data[i] >= 'A' && s->data[i] <= 'Z')
                s->data[i] |= 32;
        }
    }
}

/**
 * @brief Converts all the lowercase characters in a string to uppercase.
 *
 * @param s A pointer to the string to be converted to uppercase.
 */
void string_to_upper(const lite_string *const restrict s) {
    if (s) {
        for (size_t i = 0; i < s->size; ++i) {
            if (s->data[i] >= 'a' && s->data[i] <= 'z')
                s->data[i] &= ~32;
        }
    }
}

/**
 * @brief Converts a string to title case.
 *
 * @param s A pointer to the string to be converted to title case.
 */
void string_to_title(const lite_string *const restrict s) {
    if (s) {
        if (s->data[0] >= 'a' && s->data[0] <= 'z')
            s->data[0] &= ~32;

        // Iterate over the rest of the string
        for (size_t i = 1; i < s->size; ++i) {
            if (s->data[i] == ' ' && s->data[i + 1] >= 'a' && s->data[i + 1] <= 'z')
                s->data[i + 1] &= ~32;
        }
    }
}

/**
 * @brief Replaces all occurrences of a substring in a string with another substring.
 *
 * @param s A pointer to the string where the substrings will be replaced.
 * @param old_sub A pointer to the substring to be replaced.
 * @param new_sub A pointer to the substring that will replace the old substring.
 * @return true if the substrings were successfully replaced, false otherwise.
 */
bool string_replace(lite_string *const restrict s, const lite_string *const restrict old_sub,
                    const lite_string *const restrict new_sub) {
    if (s && old_sub && new_sub) {
        if (old_sub->size == 0) return true;
        if (old_sub->size > s->size) return false;

        size_t count = 0;
        size_t start = 0;
        while ((start = string_find_from(s, old_sub, start)) != lite_string_npos) {
            if (string_erase_range(s, start, old_sub->size)) {
                if (!string_insert_range(s, new_sub, start, new_sub->size)) return false;
                start += new_sub->size;
                ++count;
            }
        }
        return count > 0;
    }
    return false;
}


/**
 * @brief Replaces all occurrences of a character in a string with another character.
 *
 * @param s A pointer to the string where the characters will be replaced.
 * @param old_char The character to be replaced.
 * @param new_char The character to replace the old character.
 */
void string_replace_char(const lite_string *const restrict s, const char old_char, const char new_char) {
    if (s && old_char != new_char) {
        for (size_t i = 0; i < s->size; ++i) {
            if (s->data[i] == old_char)
                s->data[i] = new_char;
        }
    }
}

/**
 * @brief Replaces all occurrences of a C-string in a string with another C-string.
 *
 * @param s A pointer to the string where the C-strings will be replaced.
 * @param old_cstr The C-string to be replaced.
 * @param new_cstr The C-string that will replace the old C-string.
 * @return true if the C-strings were successfully replaced, false otherwise.
 */
bool string_replace_cstr(lite_string *const restrict s, const char *const restrict old_cstr,
                         const char *const restrict new_cstr) {
    if (s && old_cstr && new_cstr) {
        const size_t old_len = strlen(old_cstr);
        const size_t new_len = strlen(new_cstr);
        if (old_len == 0) return true;
        if (old_len > s->size) return false;

        size_t count = 0;
        size_t start = 0;
        while ((start = string_find_cstr_from(s, old_cstr, start)) != lite_string_npos) {
            if (string_erase_range(s, start, old_len)) {
                if (!string_insert_cstr_range(s, new_cstr, start, new_len)) return false;
                start += new_len;
                ++count;
            }
        }
        return count > 0;
    }
    return false;
}

/**
 * @brief Duplicates a string.
 *
 * @param s A pointer to the string to be duplicated.
 * @return A pointer to the new string, or NULL if the duplication failed.
 *
 * @note The returned pointer must be freed by the caller, using the \p string_free() function.
 */
LITE_ATTR_NODISCARD lite_string *string_duplicate(const lite_string *const restrict s) {
    if (s) {
        lite_string *dup = string_new();
        if (dup) {
            if (string_copy(s, dup)) {
                return dup;
            }
            string_free(dup);
        }
    }
    return nullptr;
}

/**
 * @brief Reverses the order of characters in a string.
 *
 * @param s A pointer to the string to be reversed.
 */
void string_reverse(const lite_string *const restrict s) {
    if (s) {
        // Iterate over the first half of the string
        for (size_t i = 0; i < s->size / 2; ++i) {
            // Swap the character at the current position with the character at the symmetric position from the end
            const char tmp = s->data[i];
            s->data[i] = s->data[s->size - i - 1];
            s->data[s->size - i - 1] = tmp;
        }
    }
}

/**
 * @brief Converts a string to a long long integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The long long integer representation of the string, or 0 if the string is NULL.
 */
long long string_to_ll(lite_string *const restrict s) {
    long long result = 0;
    if (s) result = strtoll(string_cstr(s), nullptr, 10);
    return result;
}

/**
 * @brief Converts a string to an unsigned long long integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The unsigned long long integer representation of the string, or 0 if the string is NULL.
 */
unsigned long long string_to_ull(lite_string *const restrict s) {
    unsigned long long result = 0;
    if (s) result = strtoull(string_cstr(s), nullptr, 10);
    return result;
}

/**
 * @brief Converts a string to a long integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The long integer representation of the string, or 0 if the string is NULL.
 */
long string_to_l(lite_string *const restrict s) {
    long result = 0;
    if (s) result = strtol(string_cstr(s), nullptr, 10);
    return result;
}

/**
 * @brief Converts a string to an unsigned long integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The unsigned long integer representation of the string, or 0 if the string is NULL.
 */
unsigned long string_to_ul(lite_string *const restrict s) {
    unsigned long result = 0;
    if (s) result = strtoul(string_cstr(s), nullptr, 10);
    return result;
}

/**
 * @brief Converts a string to an integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The integer representation of the string, or 0 if the string is NULL.
 */
int string_to_int(lite_string *const restrict s) {
    return (int) string_to_l(s);
}

/**
 * @brief Converts a string to an unsigned integer.
 *
 * @param s A pointer to the string to be converted.
 * @return The unsigned integer representation of the string, or 0 if the string is NULL.
 */
unsigned int string_to_uint(lite_string *const restrict s) {
    return (unsigned int) string_to_ul(s);
}

/**
 * @brief Converts a string to a double.
 *
 * @param s A pointer to the string to be converted.
 * @return The double representation of the string, or 0.0 if the string is NULL.
 */
double string_to_double(lite_string *const restrict s) {
    double result = 0.0;
    if (s) result = strtod(string_cstr(s), nullptr);
    return result;
}

/**
 * @brief Converts a string to a float.
 *
 * @param s A pointer to the string to be converted.
 * @return The float representation of the string, or 0.0f if the string is NULL.
 */
float string_to_float(lite_string *const restrict s) {
    float result = 0.0f;
    if (s) result = strtof(string_cstr(s), nullptr);
    return result;
}

/**
 * @brief Converts a string to a long double.
 *
 * @param s A pointer to the string to be converted.
 * @return The long double representation of the string, or 0.0 if the string is NULL.
 */
long double string_to_ldouble(lite_string *const restrict s) {
    long double result = 0.0;
    if (s) result = strtold(string_cstr(s), nullptr);
    return result;
}

/**
 * @brief Converts a long long integer to a string.
 *
 * @param value The long long integer to be converted.
 * @return A pointer to the new string containing the long long integer, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ll(const long long value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%lld", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts an unsigned long long integer to a string.
 *
 * @param value The unsigned long long integer to be converted.
 * @return A pointer to the new string containing the unsigned long long integer, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ull(const unsigned long long value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%llu", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts a long integer to a string.
 *
 * @param value The long integer to be converted.
 * @return A pointer to the new string containing the long integer, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_l(const long value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%ld", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts an unsigned long integer to a string.
 *
 * @param value The unsigned long integer to be converted.
 * @return A pointer to the new string containing the unsigned long integer, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ul(const unsigned long value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%lu", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts an integer to a string.
 *
 * @param value The integer to be converted.
 * @return A pointer to the new string containing the integer.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_int(const int value) {
    return string_from_l(value);
}

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param value The unsigned integer to be converted.
 * @return A pointer to the new string containing the unsigned integer.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_uint(const unsigned int value) {
    return string_from_ul(value);
}

/**
 * @brief Converts a double to a string.
 *
 * @param value The double to be converted.
 * @return A pointer to the new string containing the double, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_double(const double value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%f", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts a float to a string.
 *
 * @param value The float to be converted.
 * @return A pointer to the new string containing the float, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_float(const float value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%f", value);
        string_append_cstr(s, buf);
    }
    return s;
}

/**
 * @brief Converts a long double to a string.
 *
 * @param value The long double to be converted.
 * @return A pointer to the new string containing the long double, or NULL if the string creation failed.
 * @note The returned pointer must be freed by the caller, using \p string_free()
 */
LITE_ATTR_NODISCARD LITE_ATTR_UNSEQUENCED lite_string *string_from_ldouble(const long double value) {
    lite_string *s = string_new();
    if (s) {
        char buf[32];
        snprintf(buf, sizeof(buf), "%Lf", value);
        string_append_cstr(s, buf);
    }
    return s;
}
