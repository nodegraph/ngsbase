set(sources
    main.cpp
)

set(headers
)
    
# Add the executable object.
if (${ARCH} STREQUAL ARCH_MACOS)
	add_executable(testraytrace MACOSX_BUNDLE ${sources} ${headers})
else()
	add_executable(testraytrace ${sources} ${headers})
endif()

# Link libraries.
target_link_libraries(testraytrace 
	)

# Install.
INSTALL(TARGETS testraytrace
	RUNTIME DESTINATION bin
	COMPONENT unittests
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	BUNDLE DESTINATION .
)




