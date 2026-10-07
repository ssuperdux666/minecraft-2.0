cmake_minimum_required(VERSION 3.10)
project(autoTexturer)

add_executable(autoTexturer
    src/main.cpp
)

target_link_options(autoTexturer PRIVATE
    -static-libgcc
    -static-libstdc++
    -static
)