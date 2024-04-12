#include <gtest/gtest.h>
#include "../lite_string.h"


TEST(LiteStringTest, FindLastOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_of(s, 'o'), 8);
    string_free(s);
}

TEST(LiteStringTest, FindLastOfReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_of(s, 'z'), lite_string_npos);
    string_free(s);
}

TEST(LiteStringTest, FindLastNotOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_last_not_of(s, '!'), 11);
    string_free(s);
}

TEST(LiteStringTest, FindFirstFromReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_from(s, 'o', 5), 8);
    string_free(s);
}

TEST(LiteStringTest, FindFirstOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_of(s, 'o'), 4);
    string_free(s);
}

TEST(LiteStringTest, FindFirstNotOfReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_first_not_of(s, 'H'), 1);
    string_free(s);
}

TEST(LiteStringTest, FindSubstrFromFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_find_from(s, sub, 0), 7);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, FindSubstrFromReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Planet");
    EXPECT_EQ(string_find_from(s, sub, 0), lite_string_npos);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, FindSubstrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_find(s, sub), 7);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, RFindSubstrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World! World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_EQ(string_rfind(s, sub), 14);
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, FindSubstrCStrFromFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr_from(s, "World", 0), 7);
    string_free(s);
}

TEST(LiteStringTest, RFindSubstrCStrFindsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World! World!");
    EXPECT_EQ(string_rfind_cstr(s, "World"), 14);
    string_free(s);
}


TEST(LiteStringTest, FindSubstrCStrReturnsCorrectIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr(s, "World"), 7);
    string_free(s);
}

TEST(LiteStringTest, FindSubstrCStrReturnsMaxSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_EQ(string_find_cstr(s, "Planet"), lite_string_npos);
    string_free(s);
}
