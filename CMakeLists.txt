cmake_minimum_required(VERSION 3.3)
project(BasketballSim)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES

main.cpp
        Player.h
        Player.cpp
        Team.cpp
        Team.h
        ProbMatrix.cpp
        ProbMatrix.h
        read_csv.cpp
    sym_mat.cpp
    sym_mat.h)

add_executable(BasketballSim ${SOURCE_FILES})