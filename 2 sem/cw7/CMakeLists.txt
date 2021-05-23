cmake_minimum_required(VERSION 3.17)
project(kp7 C)

set(CMAKE_C_STANDARD 99)

add_executable(kp7 main.c vector_i.c vector_d.c matrix.c)