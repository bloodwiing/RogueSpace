include( GNUInstallDirs )

add_library( stb INTERFACE )
set_target_properties( stb PROPERTIES LINKER_LANGUAGE C )
target_include_directories( stb
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

install( TARGETS stb
        EXPORT stb )
install( DIRECTORY stb
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN "CMakeLists.txt" EXCLUDE )
install( EXPORT stb
        FILE stbConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake )
