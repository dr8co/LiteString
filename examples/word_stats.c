#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../lite_string.h"

#ifndef S_ISREG // Not defined in Windows
#define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#endif

// A simple program that reads a file and prints the number of words and characters in the file.
int main(const int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    // Store the filename in a new lite_string object.
    lite_string *s = string_new_cstr(argv[1]);

    // Get the file properties.
    struct stat st = {0};
    if (stat(string_cstr(s), &st) != 0) {
        perror("stat");
        string_free(s);
        return 1;
    }
    // The file must be a regular file.
    if (!S_ISREG(st.st_mode)) {
        fputs("Error: Not a regular file.\n", stderr);
        string_free(s);
        return 1;
    }
    // If the file size is greater than 1 MB, return an error.
    const size_t file_size = st.st_size;
    if (file_size > 1 << 20) {
        fputs("Error: File size is too large.\n", stderr);
        string_free(s);
        return 1;
    }
    // If the file is empty, return an error.
    if (file_size == 0) {
        fputs("Error: File is empty.\n", stderr);
        string_free(s);
        return 1;
    }
    // Open the file
#if _MSC_VER
    // MSVC deprecates fopen, use fopen_s instead.
    FILE *file;
    errno_t err = fopen_s(&file, string_cstr(s), "rb");
    if (err != 0 || file == nullptr) {
#else
    FILE *file = fopen(string_cstr(s), "rb");
    if (file == nullptr) {
#endif
        perror("Could not open file");
        string_free(s);
        return 1;
    }
    // Read the file into a buffer.
#if _MSC_VER
    // MSVC does not support variable length arrays.

#include <stdlib.h>
    char *buffer = (char *) malloc(file_size + 1);
#else
    char buffer[file_size + 1];
#endif
    if (fread(buffer, sizeof(char), file_size, file) != file_size) {
        fputs("Failed to read the file.\n", stderr);
        return 1;
    }

    buffer[file_size] = '\0';
    fclose(file);

    // Reuse the string to store the file contents.
    string_clear(s);
    string_append_cstr(s, buffer);

#if _MSC_VER
    free(buffer);
#endif

    // Initializations
    size_t word_count = 0;
    size_t char_count = 0;
    bool in_word = false;

    // Count the number of words and characters in the file.
    for (size_t i = 0; i < string_length(s); ++i) {
        if (isspace(string_at(s, i))) {
            if (in_word) in_word = false;
        } else {
            if (!in_word) {
                in_word = true;
                ++word_count;
            }
            ++char_count;
        }
    }

    // Print the statistics.
    if (word_count && char_count) {
        printf("Word count: %zu\n", word_count);
        printf("Character count: %zu\n", char_count);
        printf("Average word length: %.2f\n", (double) char_count / word_count);
    } else fputs("The file contains binary data.\n", stderr);

    string_free(s);
    return 0;
}
