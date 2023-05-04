include( GNUInstallDirs )

add_library( json INTERFACE )
set_target_properties( json PROPERTIES LINKER_LANGUAGE C )
target_include_directories( json
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

install( TARGETS json
        EXPORT json )
install( DIRECTORY json
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN "CMakeLists.txt" EXCLUDE )
install( EXPORT json
        FILE jsonConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake )
