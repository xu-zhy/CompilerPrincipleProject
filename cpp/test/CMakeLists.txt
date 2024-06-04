cmake_minimum_required(VERSION 3.14)
project(correctness_test)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  parser_test
  parser_test.cc
  ../src/brain.cc
  ../src/brain.h
  ../src/parser.cc
  ../src/parser.h
  dependency.h
  ../src/parser_util.h
  ../src/lexemeDict.h
)
target_link_libraries(
  parser_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(parser_test)
