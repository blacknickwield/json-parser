#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace json {
class JsonValue {
public:
  enum JsonType { NULL_VALUE = 0, BOOL, NUMBER, STRING, OBJECT, ARRAY };

  explicit JsonValue(JsonType type);
  JsonValue();
  explicit JsonValue(bool value);
  explicit JsonValue(const char *value);
  // explicit JsonValue(const std::string &value);
  explicit JsonValue(std::string &&value);
  explicit JsonValue(std::vector<JsonValue> &value);
  JsonType m_type;
  struct JsonObject {
      std::string key;
      JsonValue value;
  };
  union Value {
    bool m_bool;
    double m_number;
    struct { size_t length; char *s; } m_string;
    struct { size_t size; JsonValue *values; } m_array;
    struct { size_t size; JsonObject *objects; } m_object;
  } m_value;
};
}  // namespace json
