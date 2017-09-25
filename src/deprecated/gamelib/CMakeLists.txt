
set(sources
    game.cpp
    )

set(module_h
    game.h
    )


# Accumulate the sources and headers.
list(APPEND sources)
list(APPEND headers)

# Create a library.
add_library(ngs_game  ${sources} ${headers})
generate_export_header(ngs_game EXPORT_MACRO_NAME GAMEEXPORT_EXPORT EXPORT_FILE_NAME game_export.h)

target_link_libraries(ngs_game 
	ngs_glewhelper
	SDL2
	SDL2main
	)

# Install.
INSTALL(TARGETS ngs_game 
  RUNTIME DESTINATION bin
  COMPONENT base
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  BUNDLE DESTINATION .
)








