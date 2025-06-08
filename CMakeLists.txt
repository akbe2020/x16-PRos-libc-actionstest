cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER_WORKS ON)
project(i686-PRos-libc C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(
        -ffreestanding
        -nostdlib
        -Wall
        -Wextra
)

file(GLOB_RECURSE LIBC_SOURCES "src/*.c")

include_directories("include")

add_library(i686-PRos-libc STATIC
        ${LIBC_SOURCES}
)
