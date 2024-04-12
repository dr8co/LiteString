#include <gtest/gtest.h>
#include "../lite_string.h"

TEST(LiteStringOperationsTest, SubstrReturnsCorrectString) {
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

TEST(LiteStringOperationsTest, CompareCStrReturnsTrueForEqualStrings) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_push_back(s, 'b'));
    ASSERT_TRUE(string_compare_cstr(s, "ab"));
    string_free(s);
}

TEST(LiteStringOperationsTest, CompareWorksCorrectly) {
    lite_string *s1 = string_new_cstr("abc");
    lite_string *s2 = string_new_cstr("abc");
    EXPECT_TRUE(string_compare(s1, s2));
    string_free(s1);
    string_free(s2);
}

TEST(LiteStringOperationsTest, ContainsReturnsTrueWhenSubstringExists) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_TRUE(string_contains(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, ContainsReturnsFalseWhenSubstringDoesNotExist) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Planet");
    EXPECT_FALSE(string_contains(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, StartsWithReturnsTrueWhenSubstringIsPrefix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_TRUE(string_starts_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, StartsWithReturnsFalseWhenSubstringIsNotPrefix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World");
    EXPECT_FALSE(string_starts_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, EndsWithReturnsTrueWhenSubstringIsSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("World!");
    EXPECT_TRUE(string_ends_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, EndsWithReturnsFalseWhenSubstringIsNotSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_FALSE(string_ends_with(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringOperationsTest, EndsWithCStrReturnsTrueWhenCStrIsSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_ends_with_cstr(s, "World!"));
    string_free(s);
}

TEST(LiteStringOperationsTest, EndsWithCStrReturnsFalseWhenCStrIsNotSuffix) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_ends_with_cstr(s, "Hello"));
    string_free(s);
}


TEST(LiteStringOperationsTest, ContainsCharReturnsTrueWhenCharExists) {
    lite_string *s = string_new_cstr("Hello");
    EXPECT_TRUE(string_contains_char(s, 'e'));
    string_free(s);
}

TEST(LiteStringOperationsTest, ContainsCharReturnsFalseWhenCharDoesNotExist) {
    lite_string *s = string_new_cstr("Hello");
    EXPECT_FALSE(string_contains_char(s, 'z'));
    string_free(s);
}

TEST(LiteStringOperationsTest, ContainsCharReturnsFalseForEmptyString) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_contains_char(s, 'e'));
    string_free(s);
}


// Comparing a string with a C-string for equality, ignoring case
TEST(LiteStringOperationsTest, CaseCompareCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_case_compare_cstr(s, "HELLO, WORLD!"));
    ASSERT_FALSE(string_case_compare_cstr(s, "HELLO, UNIVERSE!"));
    string_free(s);
}

// Comparing a string with a null C-string
TEST(LiteStringOperationsTest, CaseCompareWithNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_case_compare_cstr(s, nullptr));
    string_free(s);
}

// Comparing a null string with a C-string
TEST(LiteStringOperationsTest, CaseCompareCstrNullStringReturnsFalse) {
    ASSERT_FALSE(string_case_compare_cstr(nullptr, "HELLO, WORLD!"));
}

// String contains the C-string
TEST(LiteStringOperationsTest, ContainsCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_contains_cstr(s, "World"));
    ASSERT_FALSE(string_contains_cstr(s, "Universe"));
    string_free(s);
}

// String is null
TEST(LiteStringOperationsTest, ContainsCstrNullReturnsFalse) {
    ASSERT_FALSE(string_contains_cstr(nullptr, "World"));
}

// C-string is null
TEST(LiteStringOperationsTest, ContainsCstrNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_contains_cstr(s, nullptr));
    string_free(s);
}

// String and C-string are both null
TEST(LiteStringOperationsTest, ContainsCstrNullStringAndCStrReturnsFalse) {
    ASSERT_FALSE(string_contains_cstr(nullptr, nullptr));
}

// String is empty
TEST(LiteStringOperationsTest, ContainsCstrEmptyStringReturnsFalse) {
    lite_string *s = string_new();
    ASSERT_FALSE(string_contains_cstr(s, "World"));
    string_free(s);
}

// C-string is empty
TEST(LiteStringOperationsTest, ContainsCstrEmptyCStrReturnsTrue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_contains_cstr(s, ""));
    string_free(s);
}

// String and C-string are both empty
TEST(LiteStringOperationsTest, ContainsCstrEmptyStringAndCStrReturnsTrue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_contains_cstr(s, ""));
    string_free(s);
}

// String starts with the C-string
TEST(LiteStringOperationsTest, StartsWithCstrReturnsCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_starts_with_cstr(s, "Hello"));
    ASSERT_FALSE(string_starts_with_cstr(s, "World"));
    string_free(s);
}

// String is null
TEST(LiteStringOperationsTest, StartsWithCstrNullReturnsFalse) {
    ASSERT_FALSE(string_starts_with_cstr(nullptr, "Hello"));
}

// C-string is null
TEST(LiteStringOperationsTest, StartsWithCstrNullCStrReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_starts_with_cstr(s, nullptr));
    string_free(s);
}

// String and C-string are both null
TEST(LiteStringOperationsTest, StartsWithCstrNullStringAndCStrReturnsFalse) {
    ASSERT_FALSE(string_starts_with_cstr(nullptr, nullptr));
}

// String is empty
TEST(LiteStringOperationsTest, StartsWithCstrEmptyStringReturnsFalse) {
    lite_string *s = string_new();
    ASSERT_FALSE(string_starts_with_cstr(s, "Hello"));
    string_free(s);
}

// C-string is empty
TEST(LiteStringOperationsTest, StartsWithCstrEmptyCStrReturnsTrue) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_starts_with_cstr(s, ""));
    string_free(s);
}

// String and C-string are both empty
TEST(LiteStringOperationsTest, StartsWithCstrEmptyStringAndCStrReturnsTrue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_starts_with_cstr(s, ""));
    string_free(s);
}

// Comparing two identical strings, ignoring case
TEST(LiteStringOperationsTest, CaseCompareReturnsCorrectValue) {
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
TEST(LiteStringOperationsTest, CaseCompareNullStringReturnsFalse) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_case_compare(s, nullptr));
    ASSERT_FALSE(string_case_compare(nullptr, s));
    string_free(s);
}

// Comparing two null strings, ignoring case
TEST(LiteStringOperationsTest, CaseCompareNullStringsReturnsFalse) {
    ASSERT_FALSE(string_case_compare(nullptr, nullptr));
}

// Comparing two empty strings, ignoring case
TEST(LiteStringOperationsTest, CaseCompareEmptyStringsReturnsTrue) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_case_compare(s1, s2));
    string_free(s1);
    string_free(s2);
}
