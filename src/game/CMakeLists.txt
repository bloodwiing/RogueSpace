file( GLOB_RECURSE _game_SOURCE CONFIGURE_DEPENDS
        scene/*.cpp
        canvas/*.cpp )

# -----

add_library( game_lib OBJECT ${_game_SOURCE} )
include_directories( ${PROJECT_SOURCE_DIR}/include )
