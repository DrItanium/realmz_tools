cmake_minimum_required(VERSION 3.17)
project(caste_decomposer)

set(CMAKE_CXX_STANDARD 17)

add_executable(caste_decomposer main.cpp)
add_executable(security_char_translator translator.cc)