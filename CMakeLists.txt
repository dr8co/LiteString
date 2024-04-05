cmake_minimum_required(VERSION 3.28)

project(LiteStr C CXX)

set(CMAKE_C_STANDARD 23)

add_library(LiteStr STATIC lite_str.h lite_str.c)
