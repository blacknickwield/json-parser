#include <cstdlib>
#include <cstring>
#include "JsonValue.hpp"

namespace json {
JsonValue::JsonValue() : m_type(JsonType::NULL_VALUE) {

}

JsonValue::JsonValue(bool value) : m_type(JsonType::BOOL) {
    m_value.m_bool = value;
}

JsonValue::JsonValue(std::string &&value) : m_type(JsonType::STRING) {
    size_t len = value.length();
    m_value.m_string.length = len;
    m_value.m_string.s = (char *)malloc(len + 1);
    strncpy(m_value.m_string.s, value.c_str(), len);
    m_value.m_string.s[len] = '\0';
}
// JsonValue::JsonValue(const char *value) : m_type(JsonType::STRING)
// {
//   m_value.m_string = std::make_shared<std::string>(value);
// }

// JsonValue::JsonValue(const std::string &value) : m_type(JsonType::STRING)
// {
//   m_value.m_string = std::make_shared<std::string>(value);
// }

JsonValue::JsonValue() {
    
}

JsonValue::JsonValue(JsonType type) : m_type(type) {
    switch (type) {
    case JsonType::BOOL:
      /* code */
        m_value.m_bool = false;
        break;
    case JsonType::NUMBER:
        m_value.m_number = 0.0;
        break;
    case JsonType::STRING:
        m_value.m_string.length = -1;
        m_value.m_string.s = nullptr;
        break;
    case JsonType::ARRAY:
        m_value.m_array.size = -1;
        m_value.m_array.values = nullptr;
        break;
    default:
      break;
  }
}

}  // namespace json
