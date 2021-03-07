set(sources
    main.cpp
)

set(headers
)
    
# Add the executable object.
if (${ARCH} STREQUAL ARCH_MACOS)
	add_executable(testbox2d MACOSX_BUNDLE ${sources} ${headers})
else()
	add_executable(testbox2d ${sources} ${headers})
endif()

# Link libraries.
target_link_libraries(testbox2d 
	ngs_game
	Box2D
	)

if (${ARCH} STREQUAL "ARCH_IOS")
	set_target_properties(testutils PROPERTIES XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
endif()

# Install.
INSTALL(TARGETS testbox2d
	RUNTIME DESTINATION bin
	COMPONENT unittests
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	BUNDLE DESTINATION .
)




