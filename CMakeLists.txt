cmake_minimum_required(VERSION 3.13)
project(light_string C)

set(CMAKE_C_STANDARD 99)

add_executable(light_string main.c src/simple_dynamic_str.c src/simple_dynamic_str.h)