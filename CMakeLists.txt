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

add_subdirectory( lib )
link_libraries( glfw glad glm json stb yaml-cpp )

# -----

if(UNIX AND NOT APPLE)
    SET(CMAKE_SKIP_BUILD_RPATH FALSE)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH "$ORIGIN;$ORIGIN/lib")
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# -----

add_subdirectory( src )
add_subdirectory( test )

# -----

include_directories( ${CMAKE_SOURCE_DIR}/include )
target_include_directories( BuildTest PRIVATE ${CMAKE_SOURCE_DIR}/include )

link_libraries( $<TARGET_OBJECTS:jage> )
target_link_libraries( BuildTest $<TARGET_OBJECTS:jage> )

add_executable( Build ${CMAKE_SOURCE_DIR}/src/main.cpp )

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
