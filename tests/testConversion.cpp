#include <gtest/gtest.h>
#include "../lite_string.h"

TEST(LiteStringTest, ReverseNonEmptyString) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "!dlroW ,olleH");
    string_free(s);
}

TEST(LiteStringTest, ReverseEmptyString) {
    lite_string *s = string_new();
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "");
    string_free(s);
}

TEST(LiteStringTest, ReverseSingleCharacterString) {
    lite_string *s = string_new_cstr("a");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "a");
    string_free(s);
}

TEST(LiteStringTest, ReverseTwoCharacterString) {
    lite_string *s = string_new_cstr("ab");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "ba");
    string_free(s);
}

TEST(LiteStringTest, ReversePalindromeString) {
    lite_string *s = string_new_cstr("racecar");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "racecar");
    string_free(s);
}

TEST(LiteStringTest, ReverseStringWithSpaces) {
    lite_string *s = string_new_cstr("Hello, World!");
    string_reverse(s);
    const char *reversed = string_cstr(s);
    ASSERT_STREQ(reversed, "!dlroW ,olleH");
    string_free(s);
}

TEST(LiteStringTest, ConvertsLLPositiveNumber) {
    lite_string *s = string_new_cstr("1234567890");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringTest, ConvertsLLNegativeNumber) {
    lite_string *s = string_new_cstr("-1234567890");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, -1234567890);
    string_free(s);
}

TEST(LiteStringTest, ReturnsZeroLLForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const long long result = string_to_ll(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(LiteStringTest, ConvertsPositiveULLNumber) {
    lite_string *s = string_new_cstr("1234567890");
    const unsigned long long result = string_to_ull(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(LiteStringTest, ReturnsZeroForInvalidULLInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned long long result = string_to_ull(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}


TEST(StringToLong, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("1234567890");
    const long result = string_to_l(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(StringToLong, ConvertsNegativeNumber) {
    lite_string *s = string_new_cstr("-1234567890");
    const long result = string_to_l(s);
    ASSERT_EQ(result, -1234567890);
    string_free(s);
}

TEST(StringToLong, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const long result = string_to_l(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(StringToUnsignedLong, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("1234567890");
    const unsigned long result = string_to_ul(s);
    ASSERT_EQ(result, 1234567890);
    string_free(s);
}

TEST(StringToUnsignedLong, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned long result = string_to_ul(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(StringToInt, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("123456");
    const int result = string_to_int(s);
    ASSERT_EQ(result, 123456);
    string_free(s);
}

TEST(StringToInt, ConvertsNegativeNumber) {
    lite_string *s = string_new_cstr("-123456");
    const int result = string_to_int(s);
    ASSERT_EQ(result, -123456);
    string_free(s);
}

TEST(StringToInt, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const int result = string_to_int(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(StringToUInt, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("123456");
    const unsigned int result = string_to_uint(s);
    ASSERT_EQ(result, 123456);
    string_free(s);
}

TEST(StringToUInt, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const unsigned int result = string_to_uint(s);
    ASSERT_EQ(result, 0);
    string_free(s);
}

TEST(StringToDouble, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("123.456");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, 123.456);
    string_free(s);
}

TEST(StringToDouble, ConvertsNegativeNumber) {
    lite_string *s = string_new_cstr("-123.456");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, -123.456);
    string_free(s);
}

TEST(StringToDouble, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const double result = string_to_double(s);
    ASSERT_DOUBLE_EQ(result, 0.0);
    string_free(s);
}

TEST(StringToFloat, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("123.456");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, 123.456f);
    string_free(s);
}

TEST(StringToFloat, ConvertsNegativeNumber) {
    lite_string *s = string_new_cstr("-123.456");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, -123.456f);
    string_free(s);
}

TEST(StringToFloat, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const float result = string_to_float(s);
    ASSERT_FLOAT_EQ(result, 0.0f);
    string_free(s);
}

TEST(StringToLDouble, ConvertsPositiveNumber) {
    lite_string *s = string_new_cstr("123.456");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 123.456L);
    string_free(s);
}

TEST(StringToLDouble, ConvertsNegativeNumber) {
    lite_string *s = string_new_cstr("-123.456");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, -123.456L);
    string_free(s);
}

TEST(StringToLDouble, ReturnsZeroForInvalidInput) {
    lite_string *s = string_new_cstr("NotANumber");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 0.0L);
    string_free(s);
}

TEST(StringToLDouble, ConvertsScientificNotation) {
    lite_string *s = string_new_cstr("1.23e-4");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 1.23e-4L);
    string_free(s);
}

TEST(StringToLDouble, ReturnsZeroForEmptyString) {
    lite_string *s = string_new_cstr("");
    const long double result = string_to_ldouble(s);
    ASSERT_DOUBLE_EQ(result, 0.0L);
    string_free(s);
}

TEST(StringFromLL, ConvertsPositiveNumber) {
    constexpr long long value = 1234567890LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(StringFromLL, ConvertsNegativeNumber) {
    constexpr long long value = -1234567890LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "-1234567890");
    string_free(s);
}

TEST(StringFromLL, ConvertsZero) {
    constexpr long long value = 0LL;
    lite_string *s = string_from_ll(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromULL, ConvertsPositiveNumber) {
    constexpr unsigned long long value = 1234567890ULL;
    lite_string *s = string_from_ull(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(StringFromULL, ConvertsZero) {
    constexpr unsigned long long value = 0ULL;
    lite_string *s = string_from_ull(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromL, ConvertsPositiveNumber) {
    constexpr long value = 1234567890L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(StringFromL, ConvertsNegativeNumber) {
    constexpr long value = -1234567890L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "-1234567890");
    string_free(s);
}

TEST(StringFromL, ConvertsZero) {
    constexpr long value = 0L;
    lite_string *s = string_from_l(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromUL, ConvertsZero) {
    constexpr unsigned long value = 0UL;
    lite_string *s = string_from_ul(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromUL, ConvertsPositiveNumber) {
    constexpr unsigned long value = 1234567890UL;
    lite_string *s = string_from_ul(value);
    ASSERT_STREQ(string_cstr(s), "1234567890");
    string_free(s);
}

TEST(StringFromInt, ConvertsZero) {
    constexpr int value = 0;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromInt, ConvertsPositiveNumber) {
    constexpr int value = 123456789;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "123456789");
    string_free(s);
}

TEST(StringFromInt, ConvertsNegativeNumber) {
    constexpr int value = -123456789;
    lite_string *s = string_from_int(value);
    ASSERT_STREQ(string_cstr(s), "-123456789");
    string_free(s);
}

TEST(StringFromUInt, ConvertsZero) {
    constexpr unsigned int value = 0U;
    lite_string *s = string_from_uint(value);
    ASSERT_STREQ(string_cstr(s), "0");
    string_free(s);
}

TEST(StringFromUInt, ConvertsPositiveNumber) {
    constexpr unsigned int value = 123456789U;
    lite_string *s = string_from_uint(value);
    ASSERT_STREQ(string_cstr(s), "123456789");
    string_free(s);
}

TEST(StringFromDouble, ConvertsPositiveNumber) {
    constexpr double value = 123.456;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "123.456000");
    string_free(s);
}

TEST(StringFromDouble, ConvertsNegativeNumber) {
    constexpr double value = -123.456;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "-123.456000");
    string_free(s);
}

TEST(StringFromDouble, ConvertsZero) {
    constexpr double value = 0.0;
    lite_string *s = string_from_double(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}

TEST(StringFromFloat, ConvertsPositiveNumber) {
    constexpr float value = 123.456f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "123.456001");
    string_free(s);
}

TEST(StringFromFloat, ConvertsNegativeNumber) {
    constexpr float value = -123.456f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "-123.456001");
    string_free(s);
}

TEST(StringFromFloat, ConvertsZero) {
    constexpr float value = 0.0f;
    lite_string *s = string_from_float(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}

TEST(StringFromLDouble, ConvertsPositiveNumber) {
    constexpr long double value = 123.456L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "123.456000");
    string_free(s);
}

TEST(StringFromLDouble, ConvertsNegativeNumber) {
    constexpr long double value = -123.456L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "-123.456000");
    string_free(s);
}

TEST(StringFromLDouble, ConvertsZero) {
    constexpr long double value = 0.0L;
    lite_string *s = string_from_ldouble(value);
    ASSERT_STREQ(string_cstr(s), "0.000000");
    string_free(s);
}


TEST(LiteStringTest, ToLowerConvertsUppercaseToLowerCase) {
    lite_string *s = string_new_cstr("HELLO");
    string_to_lower(s);
    EXPECT_STREQ("hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToLowerLeavesLowerCaseUnchanged) {
    lite_string *s = string_new_cstr("hello");
    string_to_lower(s);
    EXPECT_STREQ("hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToUpperConvertsLowerCaseToUpperCase) {
    lite_string *s = string_new_cstr("hello");
    string_to_upper(s);
    EXPECT_STREQ("HELLO", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToUpperLeavesUpperCaseUnchanged) {
    lite_string *s = string_new_cstr("HELLO");
    string_to_upper(s);
    EXPECT_STREQ("HELLO", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToTitleConvertsFirstLetterToUpperCase) {
    lite_string *s = string_new_cstr("hello world");
    string_to_title(s);
    EXPECT_STREQ("Hello World", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToTitleLeavesTitleCaseUnchanged) {
    lite_string *s = string_new_cstr("Hello World");
    string_to_title(s);
    EXPECT_STREQ("Hello World", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToTitleHandlesSingleWord) {
    lite_string *s = string_new_cstr("hello");
    string_to_title(s);
    EXPECT_STREQ("Hello", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToTitleHandlesEmptyString) {
    lite_string *s = string_new_cstr("");
    string_to_title(s);
    EXPECT_STREQ("", string_cstr(s));
    string_free(s);
}

TEST(LiteStringTest, ToTitleHandlesSingleLetter) {
    lite_string *s = string_new_cstr("a");
    string_to_title(s);
    EXPECT_STREQ("A", string_cstr(s));
    string_free(s);
}
