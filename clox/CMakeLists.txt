cmake_minimum_required(VERSION 3.28)
project(clox C)

set(CMAKE_C_STANDARD 23)

add_executable(clox src/main.c
               src/chunk.c
               src/memory.c
               src/debug.c
               src/value.c
               src/vm.c
               src/vm.h
               src/compiler.c
               src/compiler.h
               src/scanner.c
               src/scanner.h)
