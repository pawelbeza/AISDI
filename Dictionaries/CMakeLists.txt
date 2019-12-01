cmake_minimum_required(VERSION 2.8)

project(dictionaries)
add_executable(${PROJECT_NAME} "test.cpp" "splayTreeDictionary.h" "AVLTreeDictionary.h" "benchmark.h")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)