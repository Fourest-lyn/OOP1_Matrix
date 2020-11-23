cmake_minimum_required(VERSION 3.17)
project(OOP1_Matrix)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(OOP1_Matrix
        AdvanceTest.cpp
        BasicTest.cpp
        matrix.hpp
        testint.hpp)
