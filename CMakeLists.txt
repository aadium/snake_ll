cmake_minimum_required(VERSION 3.5)
project(snake_ll)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(snake_ll main.cpp
        Snake/Snake.cpp
        Snake/Snake.h
        Food/Food.cpp
        Food/Food.h
        HealthKit/HealthKit.cpp
        HealthKit/HealthKit.h
        Bomb/Bomb.cpp
        Bomb/Bomb.h)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw/include"
)

add_library(freeglut STATIC IMPORTED)
set_target_properties(freeglut PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/lib/libfreeglut_static.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/freeglut/include"
)

# Add compile definitions for static linking
target_compile_definitions(snake_ll PRIVATE FREEGLUT_STATIC)

# Platform-specific settings
if (WIN32)
    set(OPENGL_LIBRARIES opengl32)
    set(PLATFORM_LIBRARIES winmm)
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    set(OPENGL_LIBRARIES ${OpenGL_LIBRARY})
    set(PLATFORM_LIBRARIES ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else ()
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIBRARIES ${OPENGL_LIBRARIES})
    set(PLATFORM_LIBRARIES)
endif ()

# Link against the necessary libraries
target_link_libraries(snake_ll glfw freeglut ${OPENGL_LIBRARIES} ${PLATFORM_LIBRARIES} -static)