#include <gtest/gtest.h>
#include "../lite_string.h"

TEST(LiteStringConversionTest, ReverseNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "!dlroW ,olleH");
    string_free(s);
}

TEST(LiteStringConversionTest, ReverseEmptyString) {
    lite_string *s = string_new();
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "");
    string_free(s);
}

TEST(LiteStringConversionTest, ReverseSingleCharacterString) {
    lite_string *s = string_new_cstr("a");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "a");
    string_free(s);
}

TEST(LiteStringConversionTest, ReverseTwoCharacterString) {
    lite_string *s = string_new_cstr("ab");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "ba");
    string_free(s);
}

TEST(LiteStringConversionTest, ReversePalindromeString) {
    lite_string *s = string_new_cstr("racecar");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "racecar");
    string_free(s);
}

TEST(LiteStringConversionTest, ReverseStringWithSpaces) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "!dlroW ,olleH");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsLLPositiveNumber) {
    lite_string *s = string_new_cstr("1234567890");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsLLNegativeNumber) {
    lite_string *s = string_new_cstr("-1234567890");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, -1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsZeroLLForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveULLNumberS) {
    lite_string *s = string_new_cstr("1234567890");
    const unsigned long long result = string_to_ull(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsZeroForInvalidULLInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned long long result = string_to_ull(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}


TEST(LiteStringConversionTest, ConvertsPositiveLNumberS) {
    lite_string *s = string_new_cstr("1234567890");
    const long result = string_to_l(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeLNumberS) {
    lite_string *s = string_new_cstr("-1234567890");
    const long result = string_to_l(s);
    ASSERT_EQ(result, -1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsLZeroForInvalidInputS) {
    lite_string *s = string_new_cstr("NotANumber");
    const long result = string_to_l(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveULNumberS) {
    lite_string *s = string_new_cstr("1234567890");
    const unsigned long result = string_to_ul(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsULZeroForInvalidLInputS) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned long result = string_to_ul(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveIntNumberS) {
    lite_string *s = string_new_cstr("123456");
    const int result = string_to_int(s);
    ASSERT_EQ(result, 123456);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeIntNumberS) {
    lite_string *s = string_new_cstr("-123456");
    const int result = string_to_int(s);
    ASSERT_EQ(result, -123456);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsIntZeroForInvalidInputS) {
    lite_string *s = string_new_cstr("NotANumber");
    const int result = string_to_int(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveUIntNumberS) {
    lite_string *s = string_new_cstr("123456");
    const unsigned int result = string_to_uint(s);
    ASSERT_EQ(result, 123456);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsUIZeroForInvalidInputS) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned int result = string_to_uint(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveDNumberS) {
    lite_string *s = string_new_cstr("123.456");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, 123.456);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeDNumberS) {
    lite_string *s = string_new_cstr("-123.456");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, -123.456);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsDZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, 0.0);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveFNumberS) {
    lite_string *s = string_new_cstr("123.456");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, 123.456f);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeFNumberS) {
    lite_string *s = string_new_cstr("-123.456");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, -123.456f);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsFZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, 0.0f);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveLDNumberS) {
    lite_string *s = string_new_cstr("123.456");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 123.456L);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeLDNumberS) {
    lite_string *s = string_new_cstr("-123.456");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, -123.456L);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsLDZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 0.0L);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsScientificNotation) {
    lite_string *s = string_new_cstr("1.23e-4");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 1.23e-4L);
    string_free(s);
}

TEST(LiteStringConversionTest, ReturnsZeroForEmptyString) {
    lite_string *s = string_new_cstr("");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 0.0L);
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveLLNumber) {
    constexpr long long value = 1234567890LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeLLNumber) {
    constexpr long long value = -1234567890LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "-1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsLLZero) {
    constexpr long long value = 0LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveULLNumber) {
    constexpr unsigned long long value = 1234567890ULL;
    lite_string *s = string_from_ull(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsZero) {
    constexpr unsigned long long value = 0ULL;
    lite_string *s = string_from_ull(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveLNumber) {
    constexpr long value = 1234567890L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeNumber) {
    constexpr long value = -1234567890L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "-1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsLZero) {
    constexpr long value = 0L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsULZero) {
    constexpr unsigned long value = 0UL;
    lite_string *s = string_from_ul(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveULNumber) {
    constexpr unsigned long value = 1234567890UL;
    lite_string *s = string_from_ul(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsIntZero) {
    constexpr int value = 0;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveIntNumber) {
    constexpr int value = 123456789;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "123456789");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeIntNumber) {
    constexpr int value = -123456789;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "-123456789");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsUIZero) {
    constexpr unsigned int value = 0U;
    lite_string *s = string_from_uint(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveUINumber) {
    constexpr unsigned int value = 123456789U;
    lite_string *s = string_from_uint(value);
    ASSERT_STREQ(string_cstr(s), "123456789");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveDNumber) {
    constexpr double value = 123.456;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "123.456000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeDNumber) {
    constexpr double value = -123.456;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "-123.456000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsDZero) {
    constexpr double value = 0.0;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveFNumber) {
    constexpr float value = 123.456f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "123.456001");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeFNumber) {
    constexpr float value = -123.456f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "-123.456001");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsFZero) {
    constexpr float value = 0.0f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsPositiveLDNumber) {
    constexpr long double value = 123.456L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "123.456000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsNegativeLDNumber) {
    constexpr long double value = -123.456L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "-123.456000");
    string_free(s);
}

TEST(LiteStringConversionTest, ConvertsLDZero) {
    constexpr long double value = 0.0L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}


TEST(LiteStringConversionTest, ToLowerConvertsUppercaseToLowerCase) {
    lite_string *s = string_new_cstr("HELLO");
    string_to_lower(s);
    EXPECT_STREQ("hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToLowerLeavesLowerCaseUnchanged) {
    lite_string *s = string_new_cstr("hello");
    string_to_lower(s);
    EXPECT_STREQ("hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToUpperConvertsLowerCaseToUpperCase) {
    lite_string *s = string_new_cstr("hello");
    string_to_upper(s);
    EXPECT_STREQ("HELLO", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToUpperLeavesUpperCaseUnchanged) {
    lite_string *s = string_new_cstr("HELLO");
    string_to_upper(s);
    EXPECT_STREQ("HELLO", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToTitleConvertsFirstLetterToUpperCase) {
    lite_string *s = string_new_cstr("hello world");
    string_to_title(s);
    EXPECT_STREQ("Hello World", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToTitleLeavesTitleCaseUnchanged) {
    lite_string *s = string_new_cstr("Hello World");
    string_to_title(s);
    EXPECT_STREQ("Hello World", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToTitleHandlesSingleWord) {
    lite_string *s = string_new_cstr("hello");
    string_to_title(s);
    EXPECT_STREQ("Hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToTitleHandlesEmptyString) {
    lite_string *s = string_new_cstr("");
    string_to_title(s);
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
}

TEST(LiteStringConversionTest, ToTitleHandlesSingleLetter) {
    lite_string *s = string_new_cstr("a");
    string_to_title(s);
    EXPECT_STREQ("A", string_cstr(s));
    string_free(s);
}
