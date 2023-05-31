add_subdirectory( jage )
add_subdirectory( game )

# -----

add_library( jage ALIAS jage_lib )
add_library( game ALIAS game_lib )
