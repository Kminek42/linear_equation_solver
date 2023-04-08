cmake_minimum_required(VERSION 3.24)
project(linear_equation_solver C)

set(CMAKE_C_STANDARD 11)

add_executable(linear_equation_solver
        main.c matrix.c)
