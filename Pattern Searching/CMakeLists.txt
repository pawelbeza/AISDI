cmake_minimum_required(VERSION 2.8)

project(dictionaries)
add_executable(${PROJECT_NAME} "tests.cpp" "BruteForce.cpp" "KMP.cpp" "RabinKarp.cpp")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
