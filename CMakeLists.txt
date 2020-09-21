cmake_minimum_required(VERSION 3.17)
project(realmz_tools)

set(CMAKE_CXX_STANDARD 17)

add_executable(dumpcaste CasteDecomposer.cpp BinaryManipulation.h Caste.cc Caste.h)
add_executable(realmz_keygen KeyGen.cc)