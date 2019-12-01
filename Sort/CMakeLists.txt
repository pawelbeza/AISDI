cmake_minimum_required(VERSION 2.8)

project(sort)
add_executable(${PROJECT_NAME} "test.cpp" "quick_sort.cpp" "merge_sort.cpp" "bubble_sort.cpp")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
