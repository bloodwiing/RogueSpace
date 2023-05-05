include( GNUInstallDirs )

add_library( KHR INTERFACE )
set_target_properties( KHR PROPERTIES LINKER_LANGUAGE C )
target_include_directories( KHR
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> )

install( TARGETS KHR
        EXPORT KHR )
install( DIRECTORY KHR
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        PATTERN "CMakeLists.txt" EXCLUDE )
install( EXPORT KHR
        FILE KHRConfig.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake )
