#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>
#include <base/memoryallocator/taggednew.h>
#include <base/device/geometry/textbuffers.h>
#include <iostream>

namespace ngs {

TextIBO::TextIBO(unsigned int num_quads):IndexBuffer(GL_TRIANGLES, GL_UNSIGNED_INT) {
  load(num_quads);
}

void TextIBO::load(unsigned int num_quads) {
  unsigned int * indices = new_ff unsigned int[num_quads * 6]; // 6 indices per quad, 3 indices per triangle
  for (unsigned int i=0; i<num_quads; i++) {
    unsigned int base_index = i*6;
    unsigned int base_vertex = i*4;
    indices[base_index+0] = base_vertex;
    indices[base_index+1] = base_vertex+1;
    indices[base_index+2] = base_vertex+2;
    indices[base_index+3] = base_vertex;
    indices[base_index+4] = base_vertex+2;
    indices[base_index+5] = base_vertex+3;
  }
  // Load the indices to the gpu.
  bind();
  load(num_quads * 6 * sizeof(unsigned int), indices);
  // Cleanup.
  delete_ff(indices);
}

const AttributeFormat TextVBO::pos_attr_format = { 3, GL_FLOAT, false, sizeof(PosTexVertex), (void*) 0, 0 };
const AttributeFormat TextVBO::tex_attr_format = { 2, GL_FLOAT, false, sizeof(PosTexVertex), (void*) (3 * sizeof(float)), 0 };

TextVBO::TextVBO(const PosTexVertex* verts, unsigned int num):VertexBuffer() {
  load(sizeof(PosTexVertex) * num * 4, verts);
}


}
