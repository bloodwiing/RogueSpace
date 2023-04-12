cmake_minimum_required(VERSION 3.24)
project(RogueSpace)

# -----

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# -----

link_directories(RogueSpace ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/lib/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include/GLFW/")

find_package(OpenGL REQUIRED)

# -----

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp)

# -----

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/include/glm)
add_subdirectory(test)

# -----

add_executable(Build ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_sources(Google_Tests_run PRIVATE ${SRC_FILES})

# -----

if(NOT WIN32)
    target_link_libraries(Build dl X11)
    target_link_libraries(Google_Tests_run dl X11)
endif()

target_include_directories(Build PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Google_Tests_run PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Build glfw)
target_link_libraries(Google_Tests_run glfw)

if(WIN32)
    target_link_libraries(Build opengl32)
    target_link_libraries(Google_Tests_run opengl32)
else()
    target_link_libraries(Build GL)
    target_link_libraries(Google_Tests_run GL)
endif()

# -----

add_custom_target(
        Copy_Resources ALL
        COMMENT "Copying Resources to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_SOURCE_DIR}/res
)

add_dependencies(Build Copy_Resources)
add_dependencies(Google_Tests_run Copy_Resources)
