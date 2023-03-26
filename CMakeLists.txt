cmake_minimum_required(VERSION 3.24)
project(RogueSpace)

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/glm)

add_executable(Build ${SRC_FILES})

if(NOT WIN32)
    target_link_libraries(Build dl X11)
endif()

target_include_directories(Build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Build glfw)

if(WIN32)
    target_link_libraries(Build opengl32)
else()
    target_link_libraries(Build GL)
endif()

add_custom_target(
        CopyResources ALL
        COMMENT "Copying Resources to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_BINARY_DIR}/res
)

add_dependencies(Build CopyResources)
