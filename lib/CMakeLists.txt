set( CMAKE_POLICY_DEFAULT_CMP0077 NEW )

set( BUILD_SHARED_LIBS OFF )
set( YAML_CPP_MAIN_PROJECT OFF )
set( YAML_CPP_INSTALL ON )
set( GLFW_INSTALL ON )

include(CMakePrintHelpers)
include( GNUInstallDirs )

file( GLOB LIBRARY_FOLDERS
        LIST_DIRECTORIES true
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/*" )

list( FILTER LIBRARY_FOLDERS EXCLUDE REGEX "CMakeLists.txt" )

foreach( lib ${LIBRARY_FOLDERS} )
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/${lib} )
    install( TARGETS ${lib} )
endforeach()

install( DIRECTORY glm DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} PATTERN "CMakeLists.txt" EXCLUDE )
install( EXPORT glm FILE glmConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/glm NAMESPACE glm:: )

find_package( OpenGL REQUIRED )

if( WIN32 )
    link_libraries( LIBS ${LIBS} opengl32 gdi32 )
elseif( UNIX AND NOT APPLE )
    link_libraries( dl X11 GL )
endif()
