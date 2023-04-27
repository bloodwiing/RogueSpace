cmake_minimum_required(VERSION 3.20)
project(RogueSpace)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/pdb)
include(CTest)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

# -----

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# -----

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# -----

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
link_libraries(glfw)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    message(STATUS "glm found")
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GLM_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)

if(WIN32)
    set(LIBS ${LIBS} opengl32 gdi32)
elseif(UNIX AND NOT APPLE)
    set(LIBS ${LIBS} dl X11 GL)
endif()

add_library(GLAD OBJECT "${CMAKE_CURRENT_SOURCE_DIR}/src/glad/glad.c")
link_libraries($<TARGET_OBJECTS:GLAD>)

# -----

include_directories(${INCLUDE_DIRS})

# -----

if(UNIX AND NOT APPLE)
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib")
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# -----

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp)

# -----

add_library(BuildFiles OBJECT ${SRC_FILES})
link_libraries($<TARGET_OBJECTS:BuildFiles>)

link_libraries(${LIBS})
link_directories(${LINK_DIRS})

add_executable(Build ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# -----

add_subdirectory(test)

# -----

add_custom_target(
        CopyResources ALL
        COMMENT "Copying Resources to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/res
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)


add_dependencies(Build CopyResources)
add_dependencies(BuildTest Build)
