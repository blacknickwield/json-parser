cmake_minimum_required(VERSION 3.22)

project(json-parser)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
add_executable(parser main.cpp src/JsonValue.cpp src/JsonParser.cpp)
target_include_directories(parser PUBLIC include)