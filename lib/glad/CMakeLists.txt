include( GNUInstallDirs )

add_library( glad STATIC )
set_target_properties( glad PROPERTIES LINKER_LANGUAGE C )
target_sources( glad
        PRIVATE
        "glad.c" )
target_include_directories( glad
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

install( TARGETS glad
        EXPORT glad )
install( DIRECTORY glad
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN "CMakeLists.txt" EXCLUDE )
install( EXPORT glad
        FILE gladConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake )
