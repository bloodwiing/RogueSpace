cmake_minimum_required(VERSION 3.20)
project(RogueSpace)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

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

set(SHARED_LIBRARIES)

find_package(GLFW3 REQUIRED)
if(GLFW3_FOUND)
    message(STATUS "Glfw3 found")
    include_directories(${GLFW3_INCLUDE_DIR})
    link_libraries(${GLFW3_IMPORT_LIBRARY})
    set(SHARED_LIBRARIES ${SHARED_LIBRARIES} ${GLFW3_SHARED_LIBRARIES})
endif(GLFW3_FOUND)

find_package(GLM REQUIRED)
if(GLM_FOUND)
    message(STATUS "glm found")
    include_directories(${GLM_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)

if(WIN32)
    set(LIBS opengl32 gdi32)
elseif(UNIX AND NOT APPLE)
    set(LIBS dl X11 GL)
endif()

add_library(GLAD "src/glad/glad.c")
set(LIBS ${LIBS} GLAD)

# -----

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

link_libraries(${LIBS})

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
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glad/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/*.cpp)

# -----

add_executable(Build ${SRC_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_sources(Google_Tests_run PRIVATE ${SRC_FILES})

# -----

add_custom_target(
        Copy_Resources ALL
        COMMENT "Copying Resources to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/res
)

add_custom_target(
        Copy_Shared_Libraries ALL
        COMMENT "Copying Shared Libraries to build directory"
        COMMAND ${CMAKE_COMMAND} -E copy
                ${SHARED_LIBRARIES}
                $<TARGET_FILE_DIR:Build>)

add_dependencies(Build Copy_Resources Copy_Shared_Libraries)
add_dependencies(Google_Tests_run Copy_Resources Copy_Shared_Libraries)
