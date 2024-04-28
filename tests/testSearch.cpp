#include <gtest/gtest.h>
#include "../lite_string.h"

TEST(LiteStringSearchTest, FindLastOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_of(s, 'o'), 8);
    string_free(s);
}

TEST(LiteStringSearchTest, FindLastOfReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_of(s, 'z'), lite_string_npos);
    string_free(s);
}

TEST(LiteStringSearchTest, FindLastNotOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_not_of(s, '!'), 11);
    string_free(s);
}

TEST(LiteStringSearchTest, FindFirstFromReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_from(s, 'o', 5), 8);
    string_free(s);
}

TEST(LiteStringSearchTest, FindFirstOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_of(s, 'o'), 4);
    string_free(s);
}

TEST(LiteStringSearchTest, FindFirstNotOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_not_of(s, 'H'), 1);
    string_free(s);
}

TEST(LiteStringSearchTest, FindSubstrFromFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_find_from(s, sub, 0), 7);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringSearchTest, FindSubstrFromReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Planet");
    EXPECT_EQ(string_find_from(s, sub, 0), lite_string_npos);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringSearchTest, FindSubstrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_find(s, sub), 7);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringSearchTest, RFindSubstrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World! World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_rfind(s, sub), 14);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringSearchTest, FindSubstrCStrFromFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr_from(s, "World", 0), 7);
    string_free(s);
}

TEST(LiteStringSearchTest, RFindSubstrCStrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World! World!");
    EXPECT_EQ(string_rfind_cstr(s, "World"), 14);
    string_free(s);
}


TEST(LiteStringSearchTest, FindSubstrCStrReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr(s, "World"), 7);
    string_free(s);
}

TEST(LiteStringSearchTest, FindSubstrCStrReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr(s, "Planet"), lite_string_npos);
    string_free(s);
}

TEST(LiteStringTest, FindFirstOfCStrReturnsCorrectIndex) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_first_of_chars(s, "World");
    EXPECT_EQ(index, 2);
    string_free(s);
}

TEST(LiteStringTest, FindFirstOfCStrReturnsNposWhenNotFound) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_first_of_chars(s, "XYZ");
    EXPECT_EQ(index, lite_string_npos);
    string_free(s);
}

TEST(LiteStringTest, FindFirstNotOfCStrReturnsCorrectIndex) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_first_not_of_chars(s, "Helo, ");
    EXPECT_EQ(index, 7);
    string_free(s);
}

TEST(LiteStringTest, FindFirstNotOfCStrReturnsNposWhenNotFound) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_first_not_of_chars(s, "Hello, World!");
    EXPECT_EQ(index, lite_string_npos);
    string_free(s);
}

TEST(LiteStringTest, FindLastOfCStrReturnsCorrectIndex) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_last_of_chars(s, "World");
    EXPECT_EQ(index, 11);
    string_free(s);
}

TEST(LiteStringTest, FindLastOfCStrReturnsNposWhenNotFound) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_last_of_chars(s, "XYZ");
    EXPECT_EQ(index, lite_string_npos);
    string_free(s);
}

TEST(LiteStringTest, FindLastNotOfCStrReturnsCorrectIndex) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_last_not_of_chars(s, "!dlroW");
    EXPECT_EQ(index, 6);
    string_free(s);
}

TEST(LiteStringTest, FindLastNotOfCStrReturnsNposWhenNotFound) {
    lite_string* s = string_new_cstr("Hello, World!");
    const size_t index = string_find_last_not_of_chars(s, "Hello, World!");
    EXPECT_EQ(index, lite_string_npos);
    string_free(s);
}
