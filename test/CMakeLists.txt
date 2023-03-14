cmake_minimum_required(VERSION 3.22)
project(hellotest)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(parser_test JsonTest.cpp ../src/JsonParser.cpp ../src/JsonValue.cpp)
target_link_libraries(parser_test GTest::gtest_main)
target_include_directories(parser_test PUBLIC ../include)
include(GoogleTest)
gtest_add_tests(TARGET parser_test)
