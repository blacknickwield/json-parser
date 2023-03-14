#include <stdexcept>
#include <cassert>

#include "JsonParser.hpp"

namespace json {
JsonParser::JsonParser() : m_index(-1) {

}

JsonParser::JsonParser(const std::string &content) : m_content(content), m_index(0) {

}

JsonValue JsonParser::parse(const std::string &content) {
    m_content = content;
    m_index = 0;
    return parse();
}

JsonValue JsonParser::parse() {
    skipWhiteSpaces();
    const char &c = m_content[m_index];
    if (c == 'n') {
        return parse_null();
    } else if (c == 't' || c == 'f') {
        return parse_bool();
    } else if (c == '-' || isdigit(c)) {
        return parse_number();
    } else if (c == '"') {
        return parse_string();
    } else if (c == '{') {
        return parse_object();
    } else if (c == '[') {
        return parse_array();
    }


    throw std::logic_error("parse error");
}


void JsonParser::skipWhiteSpaces() {
    size_t n = m_content.length();
    while (m_index < n && (m_content[m_index] == ' ' || m_content[m_index] == '\r' 
    || m_content[m_index] == '\t' || m_content[m_index] == '\n')) {
        ++m_index;
    }
}

JsonValue JsonParser::parse_null() {
    assert(m_content[m_index] == 'n');
    if (m_content.substr(m_index, 4) != "null") {
        throw std::logic_error("parse null error");
    }

    m_index += 4;
    return JsonValue();
}

JsonValue JsonParser::parse_bool() {
    assert(m_content[m_index] == 'f' || m_content[m_index] == 't');
    if (m_content[m_index] == 't') {
        if (m_content.substr(m_index, 4) != "true") {
            throw std::logic_error("parse true error");
        }
        m_index += 4;
        return JsonValue(true);
    } else {
        if (m_content.substr(m_index, 5) != "false") {
            throw std::logic_error("parse false error");
        }
        m_index += 5;
        return JsonValue(false);
    }
}

JsonValue JsonParser::parse_number() {
    assert(m_content[m_index] == '-' || isdigit(m_content[m_index]));
    int start_pos = m_index;
    int n = m_content.length();
    if (m_content[m_index] == '-') ++m_index;
    if (m_content[m_index] == '0') { // Leading zeros are not allowed.
        ++m_index;
        if (m_index < n && isdigit(m_content[m_index])) {
            throw std::logic_error("leading zero error");
        }
    } else {
        if (m_index < n && !isdigit(m_content[m_index])) {
            throw std::logic_error("parse number error");
        }
        while (m_index < n && isdigit(m_content[m_index])) ++m_index;
    }

    if (m_index < n && m_content[m_index] == '.') ++m_index;
    while (m_index < n && isdigit(m_content[m_index])) ++m_index;
    if (m_index < n && (m_content[m_index] == 'e' || m_content[m_index] == 'E')) ++m_index;
    if (m_index < n && (m_content[m_index] == '+' || m_content[m_index] == '-')) ++m_index;
    while (m_index < n && isdigit(m_content[m_index])) ++m_index;


    return JsonValue(std::atof(m_content.substr(start_pos, m_index - start_pos).c_str()));
}

JsonValue JsonParser::parse_string() {
    assert(m_content[m_index] == '"');
    int n = m_content.length();
    int cursor = ++m_index;
    while (true) {
        if (cursor >= n) {
            throw std::logic_error("parse string error");
        }

        if (m_content[cursor] == '"') break;
        if (m_content[cursor] == '\\') {
            throw std::logic_error("escaped charactor in string");
        }
        ++cursor;
    }
    JsonValue value(m_content.substr(m_index, cursor - m_index));
    m_index = cursor + 1;
    return value;

}

JsonValue JsonParser::parse_array() {
    assert(m_content[m_index] == '[');
    ++m_index;
    std::vector<JsonValue> values;
    int n = m_content.length();
    while (true) {
        if (m_index >= n) {
            throw std::logic_error("parse array error");
        }
        values.push_back(std::move(parse()));
        skipWhiteSpaces();
        if (m_index >= n) {
            throw std::logic_error("parse array error");
        }
        if (m_content[m_index] == ']') {
            ++m_index;
            break;
        }
        if (m_content[m_index] != ',') {
            throw std::logic_error("parse array error");
        }
        ++m_index;
    }
    JsonValue value(values);
    return value;
}

JsonValue JsonParser::parse_object() {
    assert(m_content[m_index] == '{');
    ++m_index;
    int n = m_content.length();
    std::vector<std::pair<std::string, JsonValue>> objects;
    while (true) {
        // parse key
        skipWhiteSpaces();
        if (m_index >= n) {
            throw std::logic_error("parse object error");
        }
        if (m_content[m_index] == '}') {
            break;
        }

        if (m_content[m_index] != '"') {
            throw std::logic_error("parse object error");
        }

        auto &&key = parse_string();

        // seperator check
        skipWhiteSpaces();
        if (m_index >= n) {
            throw std::logic_error("parse object error");
        }
        if (m_content[m_index] != ':') {
            throw std::logic_error("parse object error");
        }
        ++m_index;

        // parse value
        auto &&value = parse();
        objects.push_back({std::string(key.m_value.m_string.s), value});
        skipWhiteSpaces();
        if (m_index >= n) {
            throw std::logic_error("parse object error");
        }
        if (m_content[m_index] == '}') {
            break;
        }
        if (m_content[m_index] != ',') {
            throw std::logic_error("parse object error");
        }
    }
    return JsonValue(objects);
}

} // namespace json
