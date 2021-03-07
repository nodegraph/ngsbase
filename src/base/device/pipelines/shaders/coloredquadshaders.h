const char* colored_quad_vert = "#version 330\n"
    "uniform mat4 mvp;\n"
    "uniform vec4 color;\n"
    "in vec4 position;\n"
    "void main()\n"
    "{ \n"
    "    gl_Position = mvp*position;\n"
    "}\n";

const char* colored_quad_frag = "#version 330\n"
    "// Uniforms\n"
    "uniform mat4 mvp;\n"
    "uniform vec4 color;\n"
    "// Outputs\n"
    "layout(location=0) out vec4 output_color;\n"
    "void main()\n"
    "{\n"
    "    output_color=color;\n"
    "}\n";

