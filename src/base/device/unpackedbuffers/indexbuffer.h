#pragma once
#include <base/device/device_export.h>
#include <base/device/unpackedbuffers/buffer.h>

namespace ngs {

class DEVICE_EXPORT IndexBuffer : public Buffer {
 public:
  IndexBuffer(GLenum primitive_mode, GLenum index_type);
  virtual ~IndexBuffer();

  // The following methods require the IndexBuffer to be bound.
  size_t get_num_indices();
  void draw_indexed();
  void draw_indexed(GLsizei num_indices);
  void draw_indexed_instances(GLsizei num_instances, GLint base_vertex_index = 0);

  GLenum get_primitive_mode() {return _primitive_mode;}
  GLenum get_index_type() {return _index_type;}

 private:
  GLenum _primitive_mode;  //eg GL_TRIANGLES
  GLenum _index_type;

  // Index Type must be one of
  // GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or
  // GL_UNSIGNED_INT.
};

}
