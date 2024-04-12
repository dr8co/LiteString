#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../lite_string.h"

// A simple program that reads a file and prints the number of words and characters in the file.
int main(const int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    lite_string *s = string_new();
    string_append_cstr(s, argv[1]);

    // Get the file properties.
    struct stat st = {};
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
    FILE *file = fopen(string_cstr(s), "r");
    if (file == nullptr) {
        perror("Could not open file");
        string_free(s);
        return 1;
    }
    // Read the file into a buffer.
    char buffer[file_size + 1];
    fread(buffer, sizeof(char), file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Reuse the string to store the file contents.
    string_clear(s);
    string_append_cstr(s, buffer);

    // Initializations
    size_t word_count = 0;
    size_t char_count = 0;
    bool in_word = false;

    // Count the number of words and characters in the file.
    for (size_t i = 0; i < string_length(s); ++i) {
        if (isspace(string_at(s, i))) {
            if (in_word) {
                in_word = false;
            }
        } else {
            if (!in_word) {
                in_word = true;
                ++word_count;
            }
            ++char_count;
        }
    }

    printf("Word count: %zu\n", word_count);
    printf("Character count: %zu\n", char_count);
    printf("Average word length: %.2f\n", (double) char_count / word_count);

    string_free(s);
    return 0;
}
