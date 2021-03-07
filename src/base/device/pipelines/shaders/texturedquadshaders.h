const char* textured_quad_vert = "#version 330\n"
    "uniform mat4 mvp;\n"
    "uniform vec4 tint;\n"
    "in vec4 position;\n"
    "in vec2 tex_coord;\n"
    "out VertexAttributes\n"
    "{\n"
    "    smooth vec2 tex_coord;\n"
    "} attr_out;\n"
    "void main()\n"
    "{ \n"
    "    gl_Position = mvp*position;\n"
    "    attr_out.tex_coord=tex_coord;\n"
    "}\n";

const char* textured_quad_frag = "#version 330\n"
    "// Uniforms\n"
    "uniform mat4 mvp;\n"
    "uniform vec4 tint;\n"
    "uniform sampler2D tex;\n"
    "// Outputs\n"
    "layout(location=0) out vec4 output_color;\n"
    "// Inputs\n"
    "in VertexAttributes\n"
    "{\n"
    "    smooth vec2 tex_coord;\n"
    "} attr_in;\n"
    "void main()\n"
    "{\n"
    "    vec4 temp=texture(tex,attr_in.tex_coord).xyzw;\n"
    "    output_color=temp+tint;\n"
    "}\n";
