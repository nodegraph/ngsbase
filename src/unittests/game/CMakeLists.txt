set(sources
    main.cpp
)

set(headers
)
    
# Add the executable object.
if (${ARCH} STREQUAL ARCH_MACOS)
	add_executable(testgame MACOSX_BUNDLE ${sources} ${headers})
else()
	add_executable(testgame ${sources} ${headers})
endif()

# Link libraries.
target_link_libraries(testgame 
	ngs_game
	)

if (${ARCH} STREQUAL "ARCH_IOS")
	set_target_properties(testutils PROPERTIES XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
endif()

# Install.
INSTALL(TARGETS testgame
	RUNTIME DESTINATION bin
	COMPONENT unittests
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	BUNDLE DESTINATION .
)




