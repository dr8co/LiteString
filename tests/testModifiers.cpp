#include <gtest/gtest.h>
#include "../lite_string.h"

TEST(LiteStringModifiersTest, PushBackIncreasesSize) {
    lite_string *s = string_new();
    EXPECT_TRUE(string_push_back(s, 'a'));
    EXPECT_EQ(string_length(s), 1);
    string_free(s);
}

TEST(LiteStringModifiersTest, PushBackStoresCorrectValue) {
    lite_string *s = string_new();
    EXPECT_TRUE(string_push_back(s, 'a'));
    EXPECT_EQ(string_at(s, 0), 'a');
    string_free(s);
}

TEST(LiteStringModifiersTest, PopBackDecreasesSize) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    string_pop_back(s);
    EXPECT_EQ(string_length(s), 0);
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertIncreasesSize) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_insert(s, 0, 'a'));
    EXPECT_EQ(string_length(s), 1);
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertStoresCorrectValue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_insert(s, 0, 'a'));
    EXPECT_EQ(string_at(s, 0), 'a');
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseDecreasesSize) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_erase(s, 0));
    EXPECT_EQ(string_length(s), 0);
    string_free(s);
}

TEST(LiteStringModifiersTest, ClearResetsSize) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    string_clear(s);
    EXPECT_EQ(string_length(s), 0);
    string_free(s);
}

TEST(LiteStringModifiersTest, AppendIncreasesSize) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_push_back(s1, 'a'));
    ASSERT_TRUE(string_push_back(s2, 'b'));
    string_append(s1, s2);
    EXPECT_EQ(string_length(s1), 2);
    string_free(s1);
    string_free(s2);
}

TEST(LiteStringModifiersTest, AppendStoresCorrectValues) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_push_back(s1, 'a'));
    ASSERT_TRUE(string_push_back(s2, 'b'));
    string_append(s1, s2);
    EXPECT_EQ(string_at(s1, 0), 'a');
    EXPECT_EQ(string_at(s1, 1), 'b');
    string_free(s1);
    string_free(s2);
}

TEST(LiteStringModifiersTest, PushBackIncreasesCapacityWhenNeeded) {
    lite_string *s = string_new();
    for (int i = 0; i < 17; ++i) {
        ASSERT_TRUE(string_push_back(s, 'a'));
    }
    EXPECT_GT(string_capacity(s), static_cast<size_t>(16));
    string_free(s);
}

TEST(LiteStringModifiersTest, PopBackDoesNotDecreaseCapacity) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    const size_t old_capacity = string_capacity(s);
    string_pop_back(s);
    EXPECT_EQ(string_capacity(s), old_capacity);
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertIncreasesCapacityWhenNeeded) {
    lite_string *s = string_new();
    for (int i = 0; i < 17; ++i) {
        ASSERT_TRUE(string_insert(s, 0, 'a'));
    }
    EXPECT_GT(string_capacity(s), static_cast<size_t>(16));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRemovesCorrectValue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_push_back(s, 'b'));
    string_erase(s, 0);
    EXPECT_EQ(string_at(s, 0), 'b');
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseDoesNotDecreaseCapacity) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    const size_t old_capacity = string_capacity(s);
    ASSERT_TRUE(string_erase(s, 0));
    EXPECT_EQ(string_capacity(s), old_capacity);
    string_free(s);
}

TEST(LiteStringModifiersTest, ClearDoesNotDecreaseCapacity) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    const size_t old_capacity = string_capacity(s);
    string_clear(s);
    EXPECT_EQ(string_capacity(s), old_capacity);
    string_free(s);
}

TEST(LiteStringModifiersTest, AppendIncreasesCapacityWhenNeeded) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    for (int i = 0; i < 9; ++i) {
        ASSERT_TRUE(string_push_back(s1, 'a'));
        ASSERT_TRUE(string_push_back(s2, 'b'));
    }
    ASSERT_TRUE(string_append(s1, s2));
    EXPECT_GT(string_capacity(s1), static_cast<size_t>(16));
    string_free(s1);
    string_free(s2);
}

TEST(LiteStringModifiersTest, SetStoresCorrectValue) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    string_set(s, 0, 'b');
    EXPECT_EQ(string_at(s, 0), 'b');
    string_free(s);
}

TEST(LiteStringModifiersTest, ConcatReturnsCorrectString) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_push_back(s1, 'a'));
    ASSERT_TRUE(string_push_back(s2, 'b'));
    lite_string *s3 = string_concat(s1, s2);
    ASSERT_EQ(string_length(s3), 2);
    EXPECT_EQ(string_at(s3, 0), 'a');
    EXPECT_EQ(string_at(s3, 1), 'b');
    string_free(s1);
    string_free(s2);
    string_free(s3);
}

TEST(LiteStringModifiersTest, AppendCStrStoresCorrectValues) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    string_append_cstr(s, "bc");
    ASSERT_EQ(string_length(s), 3);
    ASSERT_EQ(string_at(s, 1), 'b');
    ASSERT_EQ(string_at(s, 2), 'c');
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrStoresCorrectValues) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_push_back(s, 'a'));
    ASSERT_TRUE(string_push_back(s, 'b'));

    ASSERT_TRUE(string_insert_cstr(s, "cd", 1));
    ASSERT_EQ(string_length(s), 4);
    ASSERT_EQ(string_at(s, 1), 'c');
    ASSERT_EQ(string_at(s, 2), 'd');
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrInsertsAtValidIndex) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_insert_cstr(s, "Hello", 0));
    EXPECT_STREQ(string_data(s), "Hello");
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrDoesNotInsertAtInvalidIndex) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_insert_cstr(s, "Hello", 5));
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrInsertsInMiddleOfString) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_insert_cstr(s, "Hello", 0));
    ASSERT_TRUE(string_insert_cstr(s, " world", 5));
    EXPECT_STREQ(string_data(s), "Hello world");
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrDoesNotInsertNullCStr) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_insert_cstr(s, nullptr, 0));
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertCStrResizesStringIfNeeded) {
    lite_string *s = string_new();
    ASSERT_TRUE(string_insert_cstr(s, "Hello, this is a long string that will require resizing", 0));
    EXPECT_STREQ(string_data(s), "Hello, this is a long string that will require resizing");
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertRangeInsertsAtValidIndex) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello");
    ASSERT_TRUE(string_insert_range(s, sub, 0, 5));
    const char *cstr = string_cstr(s);
    EXPECT_STREQ(cstr, "Hello");
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertRangeDoesNotInsertAtInvalidIndex) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_FALSE(string_insert_range(s, sub, 5, 5));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertRangeInsertsInMiddleOfString) {
    lite_string *s = string_new_cstr("Helo");
    lite_string *sub = string_new_cstr("l");
    ASSERT_TRUE(string_insert_range(s, sub, 2, 1));
    const char *cstr = string_cstr(s);
    EXPECT_STREQ(cstr, "Hello");
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertRangeDoesNotInsertNullSubstring) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_insert_range(s, nullptr, 0, 0));
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertRangeResizesStringIfNeeded) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello, this is a long string that will require resizing");
    ASSERT_TRUE(string_insert_range(s, sub, 0, string_size(sub)));
    EXPECT_TRUE(string_compare(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertStringInsertsAtValidIndex) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello");
    ASSERT_TRUE(string_insert_string(s, sub, 0));
    EXPECT_TRUE(string_compare_cstr(s, "Hello"));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertStringDoesNotInsertAtInvalidIndex) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello");
    EXPECT_FALSE(string_insert_string(s, sub, 5));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertStringInsertsInMiddleOfString) {
    lite_string *s = string_new_cstr("Helo");
    lite_string *sub = string_new_cstr("l");
    ASSERT_TRUE(string_insert_string(s, sub, 2));
    const char *cstr = string_cstr(s);
    EXPECT_STREQ(cstr, "Hello");
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, InsertStringDoesNotInsertNullSubstring) {
    lite_string *s = string_new();
    EXPECT_FALSE(string_insert_string(s, nullptr, 0));
    string_free(s);
}

TEST(LiteStringModifiersTest, InsertStringResizesStringIfNeeded) {
    lite_string *s = string_new();
    lite_string *sub = string_new_cstr("Hello, this is a long string that will require resizing");
    ASSERT_TRUE(string_insert_string(s, sub, 0));
    EXPECT_TRUE(string_compare(s, sub));
    string_free(s);
    string_free(sub);
}

TEST(LiteStringModifiersTest, SwapSwapsContentsCorrectly) {
    lite_string *s1 = string_new_cstr("abcz");
    lite_string *s2 = string_new_cstr("def");

    const size_t size1 = string_length(s1);
    const size_t size2 = string_length(s2);

    ASSERT_TRUE(string_swap(s1, s2));
    EXPECT_EQ(string_at(s1, 0), 'd');
    EXPECT_EQ(string_at(s1, 2), 'f');

    EXPECT_EQ(string_at(s2, 0), 'a');
    EXPECT_EQ(string_at(s2, 3), 'z');

    EXPECT_EQ(size1, string_length(s2));
    EXPECT_EQ(size2, string_length(s1));

    string_free(s1);
    string_free(s2);
}

TEST(LiteStringModifiersTest, SwapHandlesEmptyStrings) {
    lite_string *s1 = string_new();
    lite_string *s2 = string_new();
    ASSERT_TRUE(string_push_back(s1, 'a'));

    ASSERT_TRUE(string_swap(s1, s2));
    EXPECT_TRUE(string_empty(s1));
    EXPECT_EQ(string_at(s2, 0), 'a');

    string_free(s1);
    string_free(s2);
}

TEST(LiteStringModifiersTest, SwapReturnsFalseForNullptr) {
    lite_string *s = string_new_cstr("abc");

    EXPECT_FALSE(string_swap(s, nullptr));
    EXPECT_FALSE(string_swap(nullptr, s));
    EXPECT_FALSE(string_swap(nullptr, nullptr));

    string_free(s);
}

TEST(LiteStringModifiersTest, ShrinkReducesSizeCorrectly) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_shrink(s, 5));
    EXPECT_EQ(string_size(s), 5);
    string_free(s);
}

TEST(LiteStringModifiersTest, ShrinkDoesNothingWhenNewSizeIsGreater) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_shrink(s, 20));
    EXPECT_EQ(string_size(s), 13);
    string_free(s);
}

TEST(LiteStringModifiersTest, ShrinkToFitReducesCapacityToSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_TRUE(string_shrink_to_fit(s));
    EXPECT_EQ(string_capacity(s), string_size(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ShrinkToFitDoesNothingWhenSizeIsCapacity) {
    lite_string *s = string_new_cstr("Hello");
    ASSERT_TRUE(string_shrink_to_fit(s));
    EXPECT_EQ(string_capacity(s), string_size(s));
    string_free(s);
}


// Test copying a non-empty string to a buffer
TEST(LiteStringModifiersTest, CopyingStringToBufferStoresCorrectValue) {
    lite_string *s = string_new_cstr("Hello, World!");
    char buf[50];
    ASSERT_TRUE(string_copy_buffer(s, buf));
    ASSERT_STREQ(buf, "Hello, World!");
    string_free(s);
}

// Test copying an empty string to a buffer
TEST(LiteStringModifiersTest, CopyingEmptyStringToBufferStoresNullCharacter) {
    lite_string *s = string_new();
    char buf[50];
    ASSERT_FALSE(string_copy_buffer(s, buf));
    string_free(s);
}

// Test copying a string to a null buffer
TEST(LiteStringModifiersTest, CopyingStringToNullBufferFails) {
    lite_string *s = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_copy_buffer(s, nullptr));
    string_free(s);
}

// Test copying a null string to a buffer
TEST(LiteStringModifiersTest, CopyingNullStringToBufferFails) {
    char buf[50];
    ASSERT_FALSE(string_copy_buffer(nullptr, buf));
}

// Copying a non-empty string to another string
TEST(LiteStringModifiersTest, CopyingStringStoresCorrectValue) {
    lite_string *src = string_new_cstr("Hello, World!");
    lite_string *dest = string_new();
    ASSERT_TRUE(string_copy(src, dest));
    ASSERT_TRUE(string_compare(src, dest));
    string_free(src);
    string_free(dest);
}

// Copying an empty string to another string
TEST(LiteStringModifiersTest, CopyingEmptyStringStoresCorrectValue) {
    lite_string *src = string_new();
    lite_string *dest = string_new();
    ASSERT_TRUE(string_copy(src, dest));
    ASSERT_TRUE(string_compare(src, dest));
    string_free(src);
    string_free(dest);
}

// Copying a string to a null string
TEST(LiteStringModifiersTest, CopyingStringToNullStringFails) {
    lite_string *src = string_new_cstr("Hello, World!");
    ASSERT_FALSE(string_copy(src, nullptr));
    string_free(src);
}

// Copying a null string to a string
TEST(LiteStringModifiersTest, CopyingNullStringFails) {
    lite_string *dest = string_new();
    ASSERT_FALSE(string_copy(nullptr, dest));
    string_free(dest);
}

TEST(LiteStringModifiersTest, ReplaceSubstringWithDifferentLengthSubstring) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("World");
    lite_string *new_sub = string_new_cstr("GitHub Copilot");
    EXPECT_TRUE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, GitHub Copilot!", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceSubstringWithSameLengthSubstring) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("World");
    lite_string *new_sub = string_new_cstr("Earth");
    EXPECT_TRUE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, Earth!", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceNonExistentSubstring) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("Universe");
    lite_string *new_sub = string_new_cstr("GitHub Copilot");
    EXPECT_FALSE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceSubstringInEmptyString) {
    lite_string *s = string_new_cstr("");
    lite_string *old_sub = string_new_cstr("World");
    lite_string *new_sub = string_new_cstr("GitHub Copilot");
    EXPECT_FALSE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceSubstringWithEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("World");
    lite_string *new_sub = string_new_cstr("");
    EXPECT_TRUE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, !", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceEmptyStringWithSubstring) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("");
    lite_string *new_sub = string_new_cstr("GitHub Copilot");
    EXPECT_TRUE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceEmptyStringWithEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    lite_string *old_sub = string_new_cstr("");
    lite_string *new_sub = string_new_cstr("");
    EXPECT_TRUE(string_replace(s, old_sub, new_sub));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
    string_free(old_sub);
    string_free(new_sub);
}

TEST(LiteStringModifiersTest, ReplaceCharInNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_replace_char(s, 'o', 'a');
    EXPECT_STREQ("Hella, Warld!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceCharInEmptyString) {
    lite_string *s = string_new_cstr("");
    string_replace_char(s, 'o', 'a');
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceCharWithItself) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_replace_char(s, 'o', 'o');
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceNonExistentChar) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_replace_char(s, 'x', 'a');
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceCStrInNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_replace_cstr(s, "World", "User"));
    EXPECT_STREQ("Hello, User!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceCStrInEmptyString) {
    lite_string *s = string_new_cstr("");
    EXPECT_FALSE(string_replace_cstr(s, "World", "User"));
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceNonExistentCStr) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_replace_cstr(s, "Universe", "User"));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceCStrWithEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_replace_cstr(s, "World", ""));
    EXPECT_STREQ("Hello, !", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, ReplaceEmptyCStrWithCStr) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_replace_cstr(s, "", "User"));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeInNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_erase_range(s, 0, 5));
    EXPECT_STREQ(", World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeAtEndOfString) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_erase_range(s, 7, 6));
    EXPECT_STREQ("Hello, ", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeExceedingStringSize) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_erase_range(s, 5, 20));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeWithCountZero) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_TRUE(string_erase_range(s, 5, 0));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeInEmptyString) {
    lite_string *s = string_new_cstr("");
    EXPECT_FALSE(string_erase_range(s, 0, 1));
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeWithNegativeCount) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_erase_range(s, 5, -1));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}

TEST(LiteStringModifiersTest, EraseRangeWithNegativeIndex) {
    lite_string *s = string_new_cstr("Hello, World!");
    EXPECT_FALSE(string_erase_range(s, -1, 5));
    EXPECT_STREQ("Hello, World!", string_cstr(s));
    string_free(s);
}
