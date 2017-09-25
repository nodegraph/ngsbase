# ---------------------------------------------------------
# OpenGL Settings.
# --------------------------------------------------------

# GLES_MAJOR_VERSION AND GLES_MINOR_VERSION define which version of opengl es to use.
# When the GLES_MAJOR_VERSION is greater than 100, it is assumed to mean desktop opengl 4.0 and greater.

set(gles_major_version 100)
set(gles_minor_version 0)

add_definitions("-DGLES_MAJOR_VERSION=${gles_major_version}")
add_definitions("-DGLES_MINOR_VERSION=${gles_minor_version}")

# You'll need to add these definitions manually in eclipse in Project/Properties/C/C++ Include Paths and Symbols.
# __pragma(x)=_Pragma("(x)")
# _wassert(a,b,c)=1
# __int64=long long
# __int32=int


# ---------------------------------------------------------
# Our build setup for windows.
# ---------------------------------------------------------

# /wd4251 disables warning about objects needing a dll interface 
# /wd4351 disables warning about msvc new behavior for default initializing an array
# /MD chooses the c runtime
# /Ob1 sets inline function expansion 
# /Od suppresses code movement to make debugging easier
# /Zi sets the debug information format
# /MP allows parallel building of source files
# /Gm- disable minimal rebuild - not compatible with parallel building?
# /GL- disalbe whole program optimization
# /P ouputs preprocessed file as *.i files somewhere in the build are - helps when debugging macros.
# /W3 set the warning level to 3
# /w34061 set the C4061 warning to report at level 3

# Debug compiler flags.
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Ob0 /Od /Debug /W3 /Zi /MP /wd4251 /wd4351") # CACHE STRING "Debug options." FORCE)
set(CMAKE_C_FLAGS_DEBUG   "/MDd /Ob0 /Od /Debug /W3 /Zi /MP /wd4251 /wd4351") # CACHE STRING "Debug options." FORCE)

# Release compiler flags.
set(CMAKE_CXX_FLAGS_RELEASE "/MD /Ob2 /O2 /MP /wd4251 /wd4351")
set(CMAKE_C_FLAGS_RELEASE   "/MD /Ob2 /O2 /MP /wd4251 /wd4351")

# Add glew defines.
add_definitions("-DGLEW_MX")

set(GLFW_DIR "${UNPACKS_DIR}/glfw-3.2.1.bin.WIN64")
include_directories("${UNPACKS_DIR}/glfw-3.2.1.bin.WIN64/include")
link_directories("${UNPACKS_DIR}/glfw-3.2.1.bin.WIN64/lib-vc2015")

