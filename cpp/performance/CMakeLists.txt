cmake_minimum_required(VERSION 3.14)
project(performance_test)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
  performance_test
  performance_test.cc
  ../src/brain.cc
  ../src/brain.h
  ../src/parser.cc
  ../src/parser.h
  ../src/parser_util.h
  ../src/lexemeDict.h
)
target_link_libraries(
    performance_test
)
