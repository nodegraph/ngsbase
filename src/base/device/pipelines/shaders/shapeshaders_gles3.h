const char* shape_vert_gles3 = "\n"
    "precision highp float;\n"
    "precision highp int;\n"
    "\n"
    "\n"
    "// Uniforms ----------------------\n"
    " uniform mat4 model_view_project;\n"
    " uniform mat4 model_view_project_selected;\n"
    "\n"
    "// Block Uniforms ----------------\n"
    "layout(std140) uniform Warpings\n"
    "{\n"
    "    vec2 warp;\n"
    "};\n"
    "\n"
    "\n"
    "// Vertex Attributes -------------\n"
    "in vec3 vertex;\n"
    "in vec2 scale;\n"
    "in float rotate;\n"
    "in vec3 translate;\n"
    "in vec3 color;\n"
    "in float state;\n"
    "\n"
    "\n"
    "// Outputs -----------------------\n"
    "out vec2 out_tex_coord;\n"
    "out vec4 out_color;\n"
    "\n"
    "\n"
    "// Program -----------------------\n"
    "void main()\n"
    "{\n"
    "    if (state >= 2.0f) {"
    "        out_color = vec4(0.9f, 0.9f, 0.0f, 1.0f);"
    "    } else { "
    "        out_color = vec4(color,1.0f);\n"
    "    }"
    "    vec3 warped = vertex;\n"
    "    warped.x *= scale.x;\n"
    "    warped.y *= scale.y;\n"
    "    float rx = cos(rotate)*warped.x - sin(rotate)*warped.y;\n"
    "    float ry = sin(rotate)*warped.x + cos(rotate)*warped.y;\n"
    "    warped = vec3(rx, ry, warped.z) + translate;\n"
    "    if (state >= 1.0f) {"
    "        gl_Position = model_view_project_selected*vec4(warped,1.0f);\n"
    "    } else {"
    "        gl_Position = model_view_project*vec4(warped,1.0f);\n"
    "    }"
    "}\n";

const char * shape_frag_gles3 = "\n"
    "precision highp float;\n"
    "precision highp int;\n"
    "in vec4 out_color;\n"
    "layout(location=0) out vec4 output_color;\n"
    "void main()\n"
    "{\n"
    "    output_color = out_color;\n"
    "}\n";
