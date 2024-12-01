cmake_minimum_required(VERSION 3.29)
project(Lab5)
project(rofl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER mpicxx)

add_executable(Lab5 main.cpp)
add_executable(rofl
        example2.cpp)

find_package(MPI REQUIRED)
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})
#target_link_libraries(Lab5 ${MPI_C_LIBRARIES})
target_link_libraries(Lab5 PUBLIC MPI::MPI_CXX)
target_link_libraries(rofl PUBLIC MPI::MPI_CXX)
