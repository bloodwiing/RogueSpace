cmake_minimum_required(VERSION 3.24)
project(RogueSpace)

# -----

set(CMAKE_CXX_STANDARD 17)
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

# -----

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# -----

add_subdirectory(test)

# -----

link_directories(RogueSpace ${CMAKE_CURRENT_SOURCE_DIR}/lib)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    message(STATUS "glm found")
    include_directories(${GLM_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)

# -----

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp)

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
                ${CMAKE_CURRENT_BINARY_DIR}/res
)

add_dependencies(Build Copy_Resources)
add_dependencies(Google_Tests_run Copy_Resources)
