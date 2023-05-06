cmake_minimum_required(VERSION 3.21)
project(cowsay C)

set(CMAKE_C_STANDARD 11)

add_executable(reading_cow reading_cow.c)
add_executable(newcow new_cow.c)
add_executable(wildcow wildcow.c)
add_executable(cow cow.c)
