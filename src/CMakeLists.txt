file( GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/graphics/*.cpp )

# -----

add_library( BuildFiles OBJECT ${SRC_FILES} )
include_directories( ${CMAKE_SOURCE_DIR}/include )
