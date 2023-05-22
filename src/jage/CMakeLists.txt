file( GLOB_RECURSE _jage_SOURCE CONFIGURE_DEPENDS
        engine.cpp
        event/*.cpp
        event/abc/*.cpp
        graphics/*.cpp
        graphics/abc/*.cpp
        graphics/mesh2d/*.cpp
        graphics/mesh3d/*.cpp
        node/*.cpp
        node/abc/*.cpp
        node/actor/*.cpp
        node/actor/abc/*.cpp
        node/base/*.cpp
        node/frame/*.cpp
        node/frame/abc/*.cpp
        runtime/*.cpp
        runtime/asset/*.cpp
        script/*.cpp
        script/abc/*.cpp
        system/*.cpp
        types/*.cpp
        utility/*.cpp )

# -----

add_library( jage_lib OBJECT ${_jage_SOURCE} )
include_directories( ${PROJECT_SOURCE_DIR}/include )
