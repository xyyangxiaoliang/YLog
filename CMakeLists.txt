cmake_minimum_required(VERSION 4.0)
project(YLog C)

set(CMAKE_C_STANDARD 99)

add_executable(YLog main.c
        YLog.h
        YLog.c)
