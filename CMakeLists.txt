cmake_minimum_required(VERSION 3.20)
project(RogueSpace)

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
include(CTest)

# -----

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# -----

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# -----

set(LINK_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(GLFW3 REQUIRED)
if(GLFW3_FOUND)
    message(STATUS "Glfw3 found")
    set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GLFW3_INCLUDE_DIR})
    set(LIBS ${LIBS} ${GLFW3_IMPORT_LIBRARY})
    set(SHARED_LIBRARIES ${SHARED_LIBRARIES} ${GLFW3_SHARED_LIBRARIES})
endif(GLFW3_FOUND)

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
    SET(CMAKE_INSTALL_RPATH $ORIGIN)
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
        ${CMAKE_CURRENT_BINARY_DIR}/res
)

add_custom_target(
        CopySharedLibraries ALL
        COMMENT "Copying Shared Libraries to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SHARED_LIBRARIES}
        $<TARGET_FILE_DIR:Build>)

add_dependencies(Build CopyResources CopySharedLibraries)
add_dependencies(BuildTest Build)
