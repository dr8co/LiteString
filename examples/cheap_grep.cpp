#include <iostream>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include "../lite_string.h"

/**
 * @brief A simple emulation of the grep command.
 *
 * This function reads the input stream line by line and prints the lines that contain the specified pattern.
 *
 * @param pattern The pattern to search for.
 * @param input The input stream to read from.
 * @param ignoreCase Whether to ignore the case of the characters.
 * @return 0 if the pattern is found, 1 otherwise.
 */
int cheap_grep(const lite_string *pattern, std::istream &input, bool ignoreCase) {
    char line[4096];
    int ret = 1;

    lite_string *s = string_new();
    lite_string *patternCopy = string_new();
    lite_string *lineCopy = string_new();

    string_copy(pattern, patternCopy);
    if (ignoreCase) string_to_lower(patternCopy);


    while (input.getline(line, sizeof line)) {
        string_append_cstr(s, line);
        string_copy(s, lineCopy);

        if (ignoreCase) string_to_lower(lineCopy);

        if (string_find_substr(lineCopy, patternCopy) != SIZE_MAX) {
            ret = 0;
            std::cout << line << '\n';
        }

        string_clear(s);
    }
    // The strings must be freed after use.
    string_free(s);
    string_free(patternCopy);
    string_free(lineCopy);

    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [-i] <pattern> <filename>\n";
        return 1;
    }

    bool ignoreCase = false;
    int argIndex = 1;
    lite_string *firstArg = string_new_cstr(argv[1]);

    if (argc > 3 && string_compare_cstr(firstArg, "-i")) {
        ignoreCase = true;
        argIndex = 2;
    }

    lite_string *pattern = string_new_cstr(argv[argIndex]);
    lite_string *filename = string_new_cstr(argv[argIndex + 1]);
    int ret = 0;

    // If the filename is "-", read from stdin.
    if (string_compare_cstr(filename, "-")) {
        ret = cheap_grep(pattern, std::cin, ignoreCase);
    } else {
        std::ifstream file(string_cstr(filename));
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file: " << std::quoted(string_cstr(filename)) << std::endl;
            ret = 1;
            goto CLEANUP;
        }
        ret = cheap_grep(pattern, file, ignoreCase);
    }

    CLEANUP: // Free the strings to release the memory.
    string_free(firstArg);
    string_free(pattern);
    string_free(filename);

    return ret;
}
