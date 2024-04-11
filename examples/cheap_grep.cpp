#include <iostream>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <memory>
#include "../lite_string.h"

/// A lambda function to clean up a lite_string object.
auto string_deleter = [](lite_string *ls) -> void { string_free(ls); };

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
    // Unique pointers to manage lite_string objects.
    std::unique_ptr<lite_string, decltype(string_deleter)> s(string_new(), string_deleter);
    std::unique_ptr<lite_string, decltype(string_deleter)> patternCopy(string_new(), string_deleter);
    std::unique_ptr<lite_string, decltype(string_deleter)> lineCopy(string_new(), string_deleter);

    string_copy(pattern, patternCopy.get());
    if (ignoreCase) string_to_lower(patternCopy.get());

    char line[4096];
    int ret{1};

    while (input.getline(line, sizeof line)) {
        string_append_cstr(s.get(), line);
        string_copy(s.get(), lineCopy.get());

        if (ignoreCase) string_to_lower(lineCopy.get());

        if (string_find_substr(lineCopy.get(), patternCopy.get()) != SIZE_MAX) {
            ret = 0;
            std::cout << line << '\n';
        }

        string_clear(s.get());
    }

    return ret;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [-i] <pattern> <filename>\n";
        return 1;
    }

    bool ignoreCase = false;
    int argIndex = 1;
    std::unique_ptr<lite_string, decltype(string_deleter)> firstArg(string_new_cstr(argv[1]), string_deleter);

    if (argc > 3 && string_compare_cstr(firstArg.get(), "-i")) {
        ignoreCase = true;
        argIndex = 2;
    }

    // Create smart pointers to manage the lifetime of the lite_string objects.
    std::unique_ptr<lite_string, decltype(string_deleter)> pattern(string_new_cstr(argv[argIndex]), string_deleter);
    std::unique_ptr<lite_string, decltype(string_deleter)> filename(string_new_cstr(argv[argIndex + 1]),
                                                                    string_deleter);

    // If the filename is "-", read from stdin.
    if (string_compare_cstr(filename.get(), "-")) {
        return cheap_grep(pattern.get(), std::cin, ignoreCase);
    } else {
        std::ifstream file(string_cstr(filename.get()));
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file: " << std::quoted(string_cstr(filename.get())) << std::endl;
            return 1;
        }
        return cheap_grep(pattern.get(), file, ignoreCase);
    }
}
