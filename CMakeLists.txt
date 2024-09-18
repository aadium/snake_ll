cmake_minimum_required(VERSION 3.0)
project(snake_ll)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake_ll main.cpp
        Snake/Snake.cpp
        Snake/Snake.h
        Food/Food.cpp
        Food/Food.h)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/include"
)

add_library(freeglut STATIC IMPORTED)
set_target_properties(freeglut PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/lib/libfreeglut.dll.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/include"
)

find_package(OpenGL REQUIRED)
target_link_libraries(snake_ll glfw freeglut OpenGL::GL)