#include <gtest/gtest.h>

#include "JsonParser.hpp"


namespace json {

TEST(JsonParserTest, NullTest) {
    JsonParser parser;
    auto value = parser.parse("null");
    EXPECT_EQ(value.m_type, JsonValue::NULL_VALUE);
}

TEST(JsonParserTest, BoolTest) {
    JsonParser parser;
    auto value_true = parser.parse("true");
    EXPECT_EQ(value_true.m_type, JsonValue::BOOL);
    EXPECT_EQ(value_true.m_value.m_bool, true);

    auto value_false = parser.parse("false");
    EXPECT_EQ(value_false.m_type, JsonValue::BOOL);
    EXPECT_EQ(value_false.m_value.m_bool, false);
}

TEST(JsonParserTest, StringTest) {
    JsonParser parser;
    auto value_empty = parser.parse("\"\"");
    EXPECT_EQ(value_empty.m_type, JsonValue::STRING);
    EXPECT_EQ(value_empty.m_value.m_string.length, 0);
    // EXPECT_EQ(value_empty.m_value.m_string.s)

    auto value_hello = parser.parse("\"Hello\"");
    EXPECT_EQ(value_hello.m_type, JsonValue::STRING);
    EXPECT_EQ(value_hello.m_value.m_string.length, 5);
}

// TEST(JsonParserTest, NumberTest) {

// }

// TEST(JsonParserTest, ArrayTest) {

// }


}
