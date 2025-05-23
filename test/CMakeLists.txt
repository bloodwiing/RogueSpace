# Note: CMake support is community-based. The maintainers do not use CMake
# internally.

cmake_minimum_required(VERSION 3.5)

if (POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

if (POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)
endif (POLICY CMP0069)

if (POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
endif (POLICY CMP0077)

set(GOOGLETEST_VERSION 1.13.0)

if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

enable_testing()

include(CMakeDependentOption)
include(GNUInstallDirs)

#Note that googlemock target already builds googletest
option(BUILD_GMOCK "Builds the googlemock subproject" ON)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" ON)
option(GTEST_HAS_ABSL "Use Abseil and RE2. Requires Abseil and RE2 to be separately added to the build." OFF)

if(BUILD_GMOCK)
    add_subdirectory( lib/googlemock )
else()
    add_subdirectory( lib/googletest )
endif()

# -----

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/jage/**/*_test.cpp)

add_executable(BuildTest ${TEST_FILES})
target_link_libraries(BuildTest gtest gtest_main gmock)

add_custom_target(
        CopyTestingResources ALL
        COMMENT "Copying Testing Resources to Testing directory"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/testres
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/testres
)
add_dependencies(BuildTest CopyTestingResources)

include(GoogleTest)
gtest_discover_tests(BuildTest)
