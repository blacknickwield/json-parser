#include <iostream>
#include "JsonParser.hpp"
#include "JsonValue.hpp"

int main(int argc, char const *argv[]) {
    std::string s = "true";
    json::JsonParser parser(s);

    auto value = parser.parse();
    std::cout << value.m_type << std::endl;
    std::cout << value.m_value.m_bool << std::endl;
    std::cout << "hello" << std::endl;    
    return 0;
}
