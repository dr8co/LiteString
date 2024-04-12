#include <gtest/gtest.h>
#include "../lite_string.h"


TEST(LiteStringTest, SubstrReturnsCorrectString) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_push_back(s, 'b'));
    ASSERT_TRUE(string_push_back(s, 'c'));
    lite_string *s2 = string_substr(s, 1, 2);
    ASSERT_NE(s2, nullptr);
    EXPECT_EQ(string_length(s2), 2);
    EXPECT_EQ(string_at(s2, 0), 'b');
    EXPECT_EQ(string_at(s2, 1), 'c');
    string_free(s);
    string_free(s2);
}

TEST(LiteStringTest, CompareCStrReturnsTrueForEqualStrings) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_push_back(s, 'b'));
    ASSERT_TRUE(string_compare_cstr(s, "ab"));
    string_free(s);
}

TEST(LiteStringTest, CompareWorksCorrectly) {
    lite_string *s1 = string_new_cstr("abc");
    lite_string *s2 = string_new_cstr("abc");
    EXPECT_TRUE(string_compare(s1, s2));
    string_free(s1);
    string_free(s2);
}

TEST(LiteStringTest, ContainsReturnsTrueWhenSubstringExists) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_TRUE(string_contains(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, ContainsReturnsFalseWhenSubstringDoesNotExist) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Planet");
    EXPECT_FALSE(string_contains(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, StartsWithReturnsTrueWhenSubstringIsPrefix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_TRUE(string_starts_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, StartsWithReturnsFalseWhenSubstringIsNotPrefix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_FALSE(string_starts_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, EndsWithReturnsTrueWhenSubstringIsSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World!");
    EXPECT_TRUE(string_ends_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, EndsWithReturnsFalseWhenSubstringIsNotSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_FALSE(string_ends_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringTest, EndsWithCStrReturnsTrueWhenCStrIsSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_ends_with_cstr(s, "World!"));
    string_free(s);
}

TEST(LiteStringTest, EndsWithCStrReturnsFalseWhenCStrIsNotSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_ends_with_cstr(s, "Hello"));
    string_free(s);
}


TEST(LiteStringTest, ContainsCharReturnsTrueWhenCharExists) {
    lite_string *s = string_new_cstr("Hello");
    EXPECT_TRUE(string_contains_char(s, 'e'));
    string_free(s);
}

TEST(LiteStringTest, ContainsCharReturnsFalseWhenCharDoesNotExist) {
    lite_string *s = string_new_cstr("Hello");
    EXPECT_FALSE(string_contains_char(s, 'z'));
    string_free(s);
}

TEST(LiteStringTest, ContainsCharReturnsFalseForEmptyString) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_contains_char(s, 'e'));
    string_free(s);
}


// Comparing a string with a C-string for equality, ignoring case
TEST(LiteStringTest, CaseCompareCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_case_compare_cstr(s, "HELLO, WORLD!"));
    ASSERT_FALSE(string_case_compare_cstr(s, "HELLO, UNIVERSE!"));
    string_free(s);
}

// Comparing a string with a null C-string
TEST(LiteStringTest, CaseCompareWithNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_case_compare_cstr(s, nullptr));
    string_free(s);
}

// Comparing a null string with a C-string
TEST(LiteStringTest, CaseCompareCstrNullStringReturnsFalse) {
    ASSERT_FALSE(string_case_compare_cstr(nullptr, "HELLO, WORLD!"));
}

// String contains the C-string
TEST(LiteStringTest, ContainsCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_contains_cstr(s, "World"));
    ASSERT_FALSE(string_contains_cstr(s, "Universe"));
    string_free(s);
}

// String is null
TEST(LiteStringTest, ContainsCstrNullReturnsFalse) {
    ASSERT_FALSE(string_contains_cstr(nullptr, "World"));
}

// C-string is null
TEST(LiteStringTest, ContainsCstrNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_contains_cstr(s, nullptr));
    string_free(s);
}

// String and C-string are both null
TEST(LiteStringTest, ContainsCstrNullStringAndCStrReturnsFalse) {
    ASSERT_FALSE(string_contains_cstr(nullptr, nullptr));
}

// String is empty
TEST(LiteStringTest, ContainsCstrEmptyStringReturnsFalse) {
    lite_string *s = string_new();
    ASSERT_FALSE(string_contains_cstr(s, "World"));
    string_free(s);
}

// C-string is empty
TEST(LiteStringTest, ContainsCstrEmptyCStrReturnsTrue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_contains_cstr(s, ""));
    string_free(s);
}

// String and C-string are both empty
TEST(LiteStringTest, ContainsCstrEmptyStringAndCStrReturnsTrue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_contains_cstr(s, ""));
    string_free(s);
}

// String starts with the C-string
TEST(LiteStringTest, StartsWithCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_starts_with_cstr(s, "Hello"));
    ASSERT_FALSE(string_starts_with_cstr(s, "World"));
    string_free(s);
}

// String is null
TEST(LiteStringTest, StartsWithCstrNullReturnsFalse) {
    ASSERT_FALSE(string_starts_with_cstr(nullptr, "Hello"));
}

// C-string is null
TEST(LiteStringTest, StartsWithCstrNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_starts_with_cstr(s, nullptr));
    string_free(s);
}

// String and C-string are both null
TEST(LiteStringTest, StartsWithCstrNullStringAndCStrReturnsFalse) {
    ASSERT_FALSE(string_starts_with_cstr(nullptr, nullptr));
}

// String is empty
TEST(LiteStringTest, StartsWithCstrEmptyStringReturnsFalse) {
    lite_string *s = string_new();
    ASSERT_FALSE(string_starts_with_cstr(s, "Hello"));
    string_free(s);
}

// C-string is empty
TEST(LiteStringTest, StartsWithCstrEmptyCStrReturnsTrue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_starts_with_cstr(s, ""));
    string_free(s);
}

// String and C-string are both empty
TEST(LiteStringTest, StartsWithCstrEmptyStringAndCStrReturnsTrue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_starts_with_cstr(s, ""));
    string_free(s);
}

// Comparing two identical strings, ignoring case
TEST(LiteStringTest, CaseCompareReturnsCorrectValue) {
    lite_string *s1 = string_new_cstr("Hello, World!");
    lite_string *s2 = string_new_cstr("HELLO, WORLD!");
    lite_string *s3 = string_new_cstr("HELLO, UNIVERSE!");

    ASSERT_TRUE(string_case_compare(s1, s2));
    ASSERT_FALSE(string_case_compare(s1, s3));
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

// Comparing a string with a null string, ignoring case
TEST(LiteStringTest, CaseCompareNullStringReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_case_compare(s, nullptr));
    ASSERT_FALSE(string_case_compare(nullptr, s));
    string_free(s);
}

// Comparing two null strings, ignoring case
TEST(LiteStringTest, CaseCompareNullStringsReturnsFalse) {
    ASSERT_FALSE(string_case_compare(nullptr, nullptr));
}

// Comparing two empty strings, ignoring case
TEST(LiteStringTest, CaseCompareEmptyStringsReturnsTrue) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_case_compare(s1, s2));
    string_free(s1);
    string_free(s2);
}
