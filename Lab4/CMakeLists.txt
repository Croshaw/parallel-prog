cmake_minimum_required(VERSION 3.29)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp") #-O3 -march=native

add_executable(Lab4 main.cpp base.hpp
        cycle.hpp
        cycle_for.hpp
        block.hpp
        block_cycle.hpp
)
