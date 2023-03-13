cmake_minimum_required(VERSION 3.24)
project(RogueSpace)
set(CMAKE_CXX_STANDARD 17)

link_directories(RogueSpace ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/")

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)

add_executable(RogueSpace ${SRC_FILES})

target_link_libraries(RogueSpace dl X11)

target_include_directories(RogueSpace PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(RogueSpace glfw)
