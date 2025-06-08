cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER_WORKS ON)
project(x16-PRos-libc C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
        -m16
        -nostdlib
        -nostdinc
        -ffreestanding
        -c
        -Wall
        -Wextra
)

file(GLOB_RECURSE LIBC_SOURCES "src/*.c" "include/*.h")

add_library(x16-PRos-libc STATIC
        ${LIBC_SOURCES}
)

target_include_directories(x16-PRos-libc PUBLIC include)
