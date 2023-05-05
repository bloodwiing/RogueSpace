file( GLOB_RECURSE _jage_SOURCE CONFIGURE_DEPENDS
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

add_library( jage_lib OBJECT ${_jage_SOURCE} )
include_directories( ${PROJECT_SOURCE_DIR}/include )
