cmake_minimum_required(VERSION 3.17)
project(24 C)

set(CMAKE_C_STANDARD 99)

add_executable(24 queue.c tree.c token.c read.h read.c tree_st.c tree_st.h token_st.h main.c)