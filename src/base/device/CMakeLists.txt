set(module_cpp 
    asyncquery.cpp
	devicedebug.cpp
	devicebasictypesgl.cpp
    )
    
set(geometry_cpp
	geometry/textlimits.cpp
	geometry/textbuffers.cpp
    geometry/controlpoint.cpp
    geometry/curve.cpp
    geometry/vertices.cpp
    geometry/shapebuffers.cpp
	)

set(packedbuffers_cpp
	packedbuffers/elementid.cpp
	packedbuffers/chunkgeometry.cpp
	packedbuffers/packedformat.cpp
	packedbuffers/packedtexture.cpp
	packedbuffers/packeduniformbuffer.cpp
	packedbuffers/packedvertexarray.cpp
    )

set(pipelines_cpp
	pipelines/coloredquadpipeline.cpp
	pipelines/texturedquadpipeline.cpp
    pipelines/shapepipeline.cpp
    pipelines/textpipeline.cpp
    )

set(program_cpp
    program/blockuniforminfos.cpp
	program/shader.cpp
	program/uniforminfo.cpp
	program/defaultuniforminfo.cpp
	program/blockuniforminfo.cpp
	program/program.cpp
	program/attributeinfo.cpp
	program/attributeinfos.cpp
	program/defaultuniforminfos.cpp
	program/fragdatainfos.cpp
)

set(transforms_cpp
    transforms/coordutil.cpp
    transforms/debugmatrix.cpp
    transforms/lens.cpp
    transforms/mouseinfo.cpp
    transforms/rayutil.cpp
    transforms/trackball.cpp
    transforms/transform.cpp
)

set(unpackedbuffers_cpp
    unpackedbuffers/texture.cpp
    unpackedbuffers/unpackedformat.cpp
    unpackedbuffers/texturebuffer.cpp
    unpackedbuffers/buffer.cpp
    unpackedbuffers/defaultunpacking.cpp
    unpackedbuffers/framebuffer.cpp
    unpackedbuffers/renderbuffer.cpp
    unpackedbuffers/uniformbuffer.cpp
    unpackedbuffers/vertexarray.cpp
    unpackedbuffers/vertexbuffer.cpp
    unpackedbuffers/indexbuffer.cpp
    )

set(vertexattributes_cpp

)

set(module_h
    asyncquery.h
	devicedebug.h
	deviceheadersgl.h
	devicebasictypesgl.h
    )
    
set(geometry_h
	geometry/textlimits.h
	geometry/textbuffers.h
	geometry/attributeformat.h
	geometry/controlpoint.h
    geometry/curve.h
    geometry/vertices.h
    geometry/shapebuffers.h
	)

set(packedbuffers_h
	packedbuffers/chunkgeometry.h
	packedbuffers/packedformat.h
	packedbuffers/packedtexture.h
	packedbuffers/packeduniformbuffer.h
	packedbuffers/packedvertexarray.h
	packedbuffers/elementid.h
    )
    
set(pipelines_h
	pipelines/coloredquadpipeline.h
	pipelines/texturedquadpipeline.h
    pipelines/shapepipeline.h
    pipelines/textpipeline.h
    )

set(program_h
    program/blockuniforminfos.h
	program/shader.h
	program/uniforminfo.h
	program/defaultuniforminfo.h
	program/blockuniforminfo.h
	program/program.h
	program/attributeinfo.h
	program/fragdatainfo.h
	program/attributeinfos.h
	program/defaultuniforminfos.h
	program/fragdatainfos.h
)

set(transforms_h
    transforms/coordutil.h
    transforms/debugmatrix.h
    transforms/glmhelper.h
    transforms/keyinfo.h
    transforms/lens.h
    transforms/mouseinfo.h
    transforms/rayutil.h
    transforms/trackball.h
    transforms/transform.h
    transforms/viewparams.h
    transforms/wheelinfo.h
)

set(unpackedbuffers_h
    unpackedbuffers/texture.h
    unpackedbuffers/unpackedformat.h
    unpackedbuffers/texturebuffer.h
    unpackedbuffers/buffer.h
    unpackedbuffers/defaultunpacking.h
    unpackedbuffers/framebuffer.h
    unpackedbuffers/renderbuffer.h
    unpackedbuffers/uniformbuffer.h
    unpackedbuffers/vertexarray.h
    unpackedbuffers/vertexbuffer.h
    unpackedbuffers/indexbuffer.h
    )

# Accumulate the sources and headers.
list(APPEND sources ${module_cpp} ${geometry_cpp} ${packedbuffers_cpp} ${pipelines_cpp} ${program_cpp} ${vertexattributes_cpp} ${transforms_cpp} ${unpackedbuffers_cpp})
list(APPEND headers ${module_h} ${geometry_h} ${packedbuffers_h} ${pipelines_h} ${program_h} ${vertexattributes_h} ${transforms_h} ${unpackedbuffers_h})

# Create a library.
add_library(ngs_device  ${sources} ${headers})
generate_export_header(ngs_device EXPORT_MACRO_NAME DEVICE_EXPORT EXPORT_FILE_NAME device_export.h)


target_link_libraries(ngs_device ngs_memoryallocator ngs_half ngs_utils)

# ARCH specific.
if (${ARCH} MATCHES "ARCH_WINDOWS")
	target_link_libraries(ngs_device 
		debug freetype-gld optimized freetype-gl
		debug freetype252_D optimized freetype252
		debug glew32mxd optimized glew32mx
		)
	target_link_libraries(ngs_device
		ngs_glewhelper
	)
elseif (${ARCH} MATCHES "ARCH_WINRT")
	target_link_libraries(ngs_device 
		debug freetype-gld optimized freetype-gl
		debug freetype252_D optimized freetype252
		debug libEGLd optimized libEGL
		debug libGLESv2d optimized libGLESv2
		)
elseif (${ARCH} MATCHES "ARCH_LINUX")
    target_link_libraries(ngs_device
	freetype
	freetype-gl
	GLEWmx GL GLU)
elseif (${ARCH} MATCHES "ARCH_MACOS")
    target_link_libraries(ngs_device 
	freetype
	freetype-gl
	GL GLU) 
elseif (${ARCH} MATCHES "ARCH_IOS")
    target_link_libraries(ngs_device 
	freetype
	freetype-gl
	${OpenGLES}
	) 
elseif (${ARCH} MATCHES "ARCH_ANDROID")
	target_link_libraries(ngs_device log)
	if (gles_major_version EQUAL 2) 
		target_link_libraries(ngs_device 
			debug freetype-gl optimized freetype-gl
			debug freetype optimized freetype
			debug GLESv2 optimized GLESv2)
	elseif (gles_major_version EQUAL 3)
		target_link_libraries(ngs_device
			debug freetype-gl optimized freetype-gl
			debug freetype optimized freetype
			debug GLESv3 optimized GLESv3
			)
	endif ()
endif ()

# Install.
INSTALL(TARGETS ngs_device
  RUNTIME DESTINATION bin
  COMPONENT base
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  BUNDLE DESTINATION .
)

