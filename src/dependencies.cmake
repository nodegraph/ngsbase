
# ---------------------------------------------------------
# Directories for our external dependencies.
# ---------------------------------------------------------

# Each platform is expected to have their dependencies in 
# the same relative location. 


# Setup variables to the root of each dependency.
set(FREETYPE_DIR "${DEPS_DIR}/freetype-2.5.2")
set(GLEW_DIR "${DEPS_DIR}/glew-1.13.0")
set(GLM_DIR "${DEPS_DIR}/../glm-0.9.8.5")
set(FREETYPE_GL_DIR "${DEPS_DIR}/freetype-gl")



# Setup up our include dirs.
include_directories("${FREETYPE_DIR}/include")
include_directories("${GLEW_DIR}/include")
include_directories("${GLM_DIR}")
include_directories("${FREETYPE_GL_DIR}/include")

# Setup up our link dirs.
link_directories("${FREETYPE_DIR}/lib/win64")
link_directories("${FREETYPE_GL_DIR}/lib/win64")

link_directories("${GLEW_DIR}/lib/Debug MX/x64")
link_directories("${GLEW_DIR}/lib/Release MX/x64")




