#pragma once
#include <base/device/device_export.h>
#include <base/device/devicebasictypesgl.h>
#include <base/device/geometry/attributeformat.h>

namespace ngs {

class VertexBuffer;
class IndexBuffer;

/*
 In order to set the vertex attribute pointers in this Vertex Array Object,
 first bind this Vertex Array Object then bind a Vertex Buffer Objects,
 then call VertexBuffer::set_vertex_attribute with appropriate parameters for each 
 vertex attribute.

 In order to set the index attribute pointers in this Vertex Array Object,
 first bind this Vertex Array Object then bind an Index Buffer Object.

 In order to draw with the info provided by the bound VertexArray, you can call
 draw on the Vertex Buffer Object or the Index Buffer Object depending on
 whether or not your geometry has an indices or not.

 */

class DEVICE_EXPORT VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  GLuint get_name() const;

  void bind();
  void unbind();

  // The following methods require the VertexArray to be bound.

  // Set vertex buffers.
  void set_float_vertex_buffer(GLuint attr_loc, const AttributeFormat& element_source, VertexBuffer* vbo);
  void set_integer_vertex_buffer(GLuint attr_loc, const AttributeFormat& element_source, VertexBuffer* vbo);

  // Draw without using the index buffers.
  static void draw_non_indexed(GLenum primitive_mode, GLint first, GLsizei count);

 private:
  void create_name();
  void remove_name();

  // Name.
  GLuint _name;
};


}
