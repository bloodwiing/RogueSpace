file( GLOB_RECURSE _JAGE_SOURCE CONFIGURE_DEPENDS
        engine.cpp
        actor/*.cpp
        actor/abc/*.cpp
        graphics/*.cpp
        graphics/model/*.cpp
        runtime/*.cpp
        script/*.cpp
        script/abc/*.cpp
        system/*.cpp
        utility/*.cpp )

# -----

add_library( JAGE_LIB OBJECT ${_JAGE_SOURCE} )
include_directories( ${PROJECT_SOURCE_DIR}/include )
