#pragma once

#include <string>

#include "JsonValue.hpp"

namespace json {
class JsonParser {
public:
    explicit JsonParser(const std::string &content);
    JsonParser();
    JsonValue parse();
    JsonValue parse(const std::string&);
private:
    JsonValue parse_null();
    JsonValue parse_bool();
    JsonValue parse_number();
    JsonValue parse_string();
    JsonValue parse_object();
    JsonValue parse_array();
private:
    void skipWhiteSpaces();
private:
    std::string m_content;
    size_t m_index;
};

}