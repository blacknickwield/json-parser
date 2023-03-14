#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

namespace json {


class JsonValue;
class JsonObject;


class JsonValue {
public:
  enum JsonType { NULL_VALUE = 0, BOOL, NUMBER, STRING, OBJECT, ARRAY };

  explicit JsonValue(JsonType type);
  JsonValue();
  explicit JsonValue(bool value);
  explicit JsonValue(double value);
  explicit JsonValue(const char *value);
  // explicit JsonValue(const std::string &value);
  explicit JsonValue(std::string &&value);
  explicit JsonValue(std::vector<JsonValue> &value);
  explicit JsonValue(std::vector<std::pair<std::string, JsonValue>> &value);

  JsonValue &operator = (bool value);
  JsonValue &operator = (double value);
  JsonValue &operator = (const char *value);
  JsonValue &operator = (std::string &&value);
  JsonValue &operator = (const JsonValue &value);
  JsonValue &operator = (const std::vector<JsonValue> &value);
  JsonValue &operator = (const std::vector<std::pair<std::string, JsonValue>> &value);


  JsonType m_type;
  
  union Value {
    bool m_bool;
    double m_number;
    struct { size_t length; char *s; } m_string;
    struct { size_t size; JsonValue *values; } m_array;
    struct { size_t size; JsonObject *objects; } m_object;
  } m_value;
};

struct JsonObject {
    std::string key;
    JsonValue value;
};

}  // namespace json
