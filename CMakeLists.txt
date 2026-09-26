cmake_minimum_required(VERSION 3.10)
project(Minecraft)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/*.c
)
add_executable(cutable ${SOURCES})

target_include_directories(cutable PRIVATE include)
target_include_directories(cutable PRIVATE config)
target_link_directories(cutable PRIVATE lib)
target_link_libraries(cutable PRIVATE glfw3dll opengl32 gdi32)

set_property(TARGET cutable PROPERTY CXX_STANDARD 17)