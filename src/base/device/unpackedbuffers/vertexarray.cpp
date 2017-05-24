#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/unpackedbuffers/vertexbuffer.h>
#include <base/device/unpackedbuffers/indexbuffer.h>

#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>

#include <iostream>
#include <cassert>

namespace ngs {

VertexArray::VertexArray() {
  create_name();
}

VertexArray::~VertexArray() {
  remove_name();
}

void VertexArray::create_name() {
  gpu(glGenVertexArrays(1, &_name));
  if (_name == 0) {
    std::cerr << "Error: insufficient memory is likely. unable to create a VertexArray.\n";
    assert(false);
  }
}

void VertexArray::remove_name() {
  if (_name != 0) {
    gpu(glDeleteVertexArrays(1, &_name));
  }
  _name = 0;
}

GLuint VertexArray::get_name() const {
  return _name;
}

void VertexArray::bind() {
  gpu(glBindVertexArray(_name));
}

void VertexArray::unbind() {
  gpu(glBindVertexArray(0));
}

void VertexArray::set_float_vertex_buffer(GLuint attr_loc, const AttributeFormat& element_source, VertexBuffer* vbo) {
  vbo->bind();
  gpu(glEnableVertexAttribArray(attr_loc));
  gpu(glVertexAttribPointer(attr_loc, element_source.num_components, element_source.type, element_source.normalized, element_source.stride, element_source.pointer));
  gpu(glVertexAttribDivisor(attr_loc, element_source.vertex_divisor));
}

void VertexArray::set_integer_vertex_buffer(GLuint attr_loc, const AttributeFormat& element_source, VertexBuffer* vbo) {
  vbo->bind();
  gpu(glEnableVertexAttribArray(attr_loc));
  gpu(glVertexAttribIPointer(attr_loc, element_source.num_components, element_source.type, element_source.stride, element_source.pointer));
  gpu(glVertexAttribDivisor(attr_loc, element_source.vertex_divisor));
}

void VertexArray::draw_non_indexed(GLenum primitive_mode, GLint first, GLsizei count) {
  gpu(glDrawArrays(primitive_mode, first, count));
}

}
