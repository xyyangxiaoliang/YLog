cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
project(YLog C)

set(CMAKE_C_STANDARD 99)

add_executable(YLog main.c
        YLog.h
        YLog.c)
