cmake_minimum_required(VERSION 3.10)
project(COMPILERPRINCIPLE LANGUAGES CXX)

set(CMAKE_CXX_COMPILE_FLAGS, "-std=c++14")

# 添加可执行文件 brain
add_executable(brain brain.cc)
target_include_directories(brain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(brain PRIVATE brain.h brain_util.h)

# 添加测试 brain_test
add_executable(brain_test brain_test.cc)
target_include_directories(brain_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(brain_test gtest_main)
target_sources(brain_test PRIVATE brain.h brain_util.h)