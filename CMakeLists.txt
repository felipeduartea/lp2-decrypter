cmake_minimum_required(VERSION 3.30)
project(lp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lp2 main.cpp
        encrypt.cpp
        encrypt.h)
