cmake_minimum_required(VERSION 4.3)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        headers.h
        function.c
        account_function.c
        admin_functions.c)
