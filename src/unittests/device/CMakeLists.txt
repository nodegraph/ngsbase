set(sources
    main.cpp
    testmemory.cpp
    testrenderoutputs.cpp
    testtexture.cpp
    testmultisampling.cpp
    testasyncquery.cpp
    testgeometryshader.cpp
)

set(headers
    testmemory.h
    testrenderoutputs.h
    testtexture.h
    testmultisampling.h
    testasyncquery.h
    testgeometryshader.h
)

# Add the executable object.
if (${ARCH} STREQUAL ARCH_MACOS)
	add_executable(testdevice MACOSX_BUNDLE ${sources} ${headers})
else()
	add_executable(testdevice ${sources} ${headers})
endif()


# Link libraries.
if (${ARCH} STREQUAL ARCH_LINUX)
	target_link_libraries(testdevice pthread )
elseif (${ARCH} STREQUAL ARCH_WINDOWS) 
	target_link_libraries(testdevice glfw3dll ngs_device)
elseif (${ARCH} STREQUAL ARCH_WINRT)
	target_link_libraries(testdevice)
elseif (${ARCH} STREQUAL DESKTOP_ANDROID)
elseif (${ARCH} STREQUAL ARCH_IOS)
	target_link_libraries(testdevice
		${ios_libs}
	)
	set_target_properties(testdevice PROPERTIES XCODE_ATTRIBUTE_ENABLE_BITCODE "NO")
endif ()

# Install.
if (NOT (${ARCH} STREQUAL ARCH_MACOS))
	INSTALL(TARGETS testdevice
	  RUNTIME DESTINATION bin
	  COMPONENT unittests
	  LIBRARY DESTINATION lib
	  ARCHIVE DESTINATION lib
	  BUNDLE DESTINATION .
	)
endif()


    

