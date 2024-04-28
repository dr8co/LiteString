#include <gtest/gtest.h>
#include "../lite_string.h"

// Creation and destruction
TEST(LiteStringGeneralTest, NewCreatesEmptyString) {
    lite_string *s = string_new();
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(string_length(s), 0);
    EXPECT_EQ(string_capacity(s), 16);
    string_free(s);
}

TEST(LiteStringGeneralTest, CStrReturnsCorrectCStr) {
    lite_string *s = string_new_cstr("abc");

    const char *cstr = string_cstr(s);
    ASSERT_EQ(cstr[3], '\0');

    ASSERT_STREQ(cstr, "abc");
    string_free(s);
}

TEST(LiteStringGeneralTest, EmptyReturnsFalseForNonEmptyString) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    EXPECT_FALSE(string_empty(s));
    string_free(s);
}

TEST(LiteStringGeneralTest, EmptyReturnsTrueForEmptyString) {
    lite_string *s = string_new();
    EXPECT_TRUE(string_empty(s));
    lite_string *s2 = string_new_cstr("abcd");
    string_clear(s2);
    EXPECT_TRUE(string_empty(s2));
    string_free(s);
    string_free(s2);
}

TEST(LiteStringGeneralTest, AtReturnsCorrectValue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    EXPECT_EQ(string_at(s, 0), 'a');
    string_free(s);
}


TEST(LiteStringGeneralTest, BackReturnsLastCharacterForNonEmptyString) {
    lite_string *s = string_new_cstr("Hi");
    EXPECT_EQ(string_back(s), 'i');
    string_free(s);
}

TEST(LiteStringGeneralTest, BackReturnsNullCharacterForEmptyString) {
    lite_string *s = string_new();
    EXPECT_EQ(string_back(s), '\0');
    string_free(s);
}

TEST(LiteStringGeneralTest, FrontReturnsFirstCharacterForNonEmptyString) {
    lite_string *s = string_new_cstr("Hi");
    EXPECT_EQ(string_front(s), 'H');
    string_free(s);
}

TEST(LiteStringGeneralTest, FrontReturnsNullCharacterForEmptyString) {
    lite_string *s = string_new();
    EXPECT_EQ(string_front(s), '\0');
    string_free(s);
}

TEST(LiteStringGeneralTest, DuplicateNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *dup = string_duplicate(s);
    EXPECT_TRUE(string_compare(s, dup));
    string_free(s);
    string_free(dup);
}

TEST(LiteStringGeneralTest, DuplicateEmptyString) {
    lite_string *s = string_new_cstr("");
    lite_string *dup = string_duplicate(s);
    EXPECT_TRUE(string_compare(s, dup));
    string_free(s);
    string_free(dup);
}

TEST(LiteStringGeneralTest, DuplicateNullString) {
    const lite_string *s = nullptr;
    lite_string *dup = string_duplicate(s);
    EXPECT_EQ(dup, nullptr);
}

TEST(LiteStringGeneralTest, FunctionsDoNotCrashForNullptr) {
    string_free(nullptr);
    EXPECT_FALSE(string_push_back(nullptr, 'a'));
    EXPECT_EQ(string_at(nullptr, 10), '\0');
    string_pop_back(nullptr);

    EXPECT_TRUE(string_empty(nullptr));
    EXPECT_FALSE(string_erase(nullptr, 17));
    EXPECT_FALSE(string_compare(nullptr, nullptr));
    EXPECT_EQ(string_length(nullptr), 0);
    EXPECT_EQ(string_capacity(nullptr), 0);
    string_clear(nullptr);

    EXPECT_FALSE(string_insert(nullptr, 1000, 'm'));
    string_set(nullptr, 0, 'x');
    EXPECT_EQ(string_substr(nullptr, 12, 30), nullptr);
    EXPECT_EQ(string_concat(nullptr, nullptr), nullptr);
    EXPECT_FALSE(string_append(nullptr, nullptr));

    EXPECT_EQ(string_cstr(nullptr), nullptr);
    EXPECT_FALSE(string_compare_cstr(nullptr, nullptr));
    EXPECT_FALSE(string_insert_cstr(nullptr, nullptr, 5));

    EXPECT_FALSE(string_insert_range(nullptr, nullptr, 99, 1102));
    EXPECT_FALSE(string_insert_string(nullptr, nullptr, 601));

    EXPECT_EQ(string_find_last_of(nullptr, 'a'), lite_string_npos);
    EXPECT_EQ(string_find_last_not_of(nullptr, 'a'), lite_string_npos);

    EXPECT_EQ(string_find_first_from(nullptr, 'a', 10), lite_string_npos);
    EXPECT_EQ(string_find_first_of(nullptr, 'a'), lite_string_npos);
    EXPECT_EQ(string_find_first_not_of(nullptr, 'a'), lite_string_npos);

    EXPECT_EQ(string_find_from(nullptr, nullptr, 17), lite_string_npos);
    EXPECT_EQ(string_find(nullptr, nullptr), lite_string_npos);

    EXPECT_EQ(string_rfind(nullptr, nullptr), lite_string_npos);
    EXPECT_EQ(string_find_cstr_from(nullptr, nullptr, 1900), lite_string_npos);
    EXPECT_EQ(string_rfind_cstr(nullptr, nullptr), lite_string_npos);
    EXPECT_EQ(string_find_cstr(nullptr, nullptr), lite_string_npos);

    EXPECT_FALSE(string_contains_char(nullptr, 'a'));
    EXPECT_FALSE(string_contains(nullptr, nullptr));

    EXPECT_FALSE(string_starts_with(nullptr, nullptr));
    EXPECT_FALSE(string_ends_with(nullptr, nullptr));
    EXPECT_FALSE(string_ends_with_cstr(nullptr, nullptr));

    EXPECT_FALSE(string_shrink(nullptr, 54));
    EXPECT_FALSE(string_shrink_to_fit(nullptr));
}
