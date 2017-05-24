
set(sources
    glewhelper.cpp
    )

set(module_h
    glewhelper.h
    )


# Accumulate the sources and headers.
list(APPEND sources)
list(APPEND headers)

# Create a library.
add_library(ngs_glewhelper  ${sources} ${headers})
generate_export_header(ngs_glewhelper EXPORT_MACRO_NAME GLEWHELPER_EXPORT EXPORT_FILE_NAME glewhelper_export.h)

target_link_libraries(ngs_glewhelper ngs_memoryallocator)

# ARCH specific.
# The glewhelper is a stub for most architectures exept the following.
# Linux and Windows without Angle.

if (${ARCH} MATCHES "ARCH_LINUX")
    target_link_libraries(ngs_glewhelper 
    	GLEWmx GL GLU)
elseif (${ARCH} MATCHES "ARCH_WINDOWS")
	target_link_libraries(ngs_glewhelper 
		debug glew32mxd optimized glew32mx 
		debug opengl32 optimized opengl32
		debug glu32 optimized glu32)
elseif (${ARCH} MATCHES "ARCH_MACOS")
elseif (${ARCH} MATCHES "ARCH_IOS")
elseif (${ARCH} MATCHES "ARCH_ANDROID")
endif ()

# Install.
INSTALL(TARGETS ngs_glewhelper 
  RUNTIME DESTINATION bin
  COMPONENT base
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  BUNDLE DESTINATION .
)


# --------------------------------------------------------------------

# Install Debug GLEW.
INSTALL(
  FILES
      "${PLATFORM_ROOT}/srcdeps/ngsexternal/vs2015/glew-1.13.0/bin/Debug MX/x64/glew32mxd.dll"
  DESTINATION bin
  COMPONENT thirdparty
  CONFIGURATIONS Debug
)

# Install Release GLEW.
INSTALL(
  FILES
      "${PLATFORM_ROOT}/srcdeps/ngsexternal/vs2015/glew-1.13.0/bin/Release MX/x64/glew32mx.dll"
  DESTINATION bin
  COMPONENT thirdparty
  CONFIGURATIONS Release
)

# Install Debug SDL2.
INSTALL(
  FILES
      "${PLATFORM_ROOT}/srcdeps/ngsexternal/vs2015/sdl2-2.0.5/lib/debug/SDL2.dll"
  DESTINATION bin
  COMPONENT thirdparty
  CONFIGURATIONS Debug
)

# Install Release SDL2.
INSTALL(
  FILES
      "${PLATFORM_ROOT}/srcdeps/ngsexternal/vs2015/sdl2-2.0.5/lib/release/SDL2.dll"
  DESTINATION bin
  COMPONENT thirdparty
  CONFIGURATIONS Release
)







