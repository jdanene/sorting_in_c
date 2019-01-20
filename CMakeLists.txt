cmake_minimum_required(VERSION 3.12)
project(kepler_challenge C)

#set(CMAKE_C_STANDARD 99)

add_executable(kepler_challenge src/sorting.cpp src/sorting.h main.c)
add_executable(main main.c)