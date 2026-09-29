cmake_minimum_required(VERSION 3.10)
project(Minecraft)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

add_executable(minecraft ${SOURCES})

target_include_directories(minecraft PRIVATE include)
target_include_directories(minecraft PRIVATE config)
target_link_directories(minecraft PRIVATE lib)
target_link_libraries(minecraft PRIVATE glfw3dll opengl32 gdi32)

set_property(TARGET minecraft PROPERTY CXX_STANDARD 17)