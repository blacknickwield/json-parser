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

TEST(JsonParserTest, NumberTest) {
    JsonParser parser;
    auto value_zero = parser.parse("0");
    EXPECT_EQ(value_zero.m_type, JsonValue::NUMBER);
    EXPECT_EQ(value_zero.m_value.m_number, 0);
    
    auto value_nzero = parser.parse("-0");
    EXPECT_EQ(value_nzero.m_type, JsonValue::NUMBER);
    EXPECT_EQ(value_zero.m_value.m_number, 0);
}


TEST(JsonParserTest, ArrayTest) {
    JsonParser parser;
    auto value = parser.parse("[null, \"Hello\", true]");
    EXPECT_EQ(value.m_type, JsonValue::ARRAY);
    EXPECT_EQ(value.m_value.m_array.size, 3);
    EXPECT_EQ(value.m_value.m_array.values[0].m_type, JsonValue::NULL_VALUE);
    EXPECT_EQ(value.m_value.m_array.values[1].m_type, JsonValue::STRING);
    EXPECT_EQ(value.m_value.m_array.values[2].m_type, JsonValue::BOOL);
    EXPECT_EQ(value.m_value.m_array.values[2].m_value.m_bool, true);
}

TEST(JsonParserTest, ObjectTest) {
    JsonParser parser;
    auto value = parser.parse("{\"a\":1}");
    EXPECT_EQ(value.m_type, JsonValue::OBJECT);
    EXPECT_EQ(value.m_value.m_object.size, 1);
    // EXPECT_EQ();

}

}
