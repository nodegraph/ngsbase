#pragma once
#include <base/device/device_export.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/geometry/vertices.h>

#include <base/device/unpackedbuffers/vertexarray.h>

namespace ngs {

class DefaultUniformInfo;
class Resources;

class Quad;
class Triangle;
class Circle;

struct PosTexVertex;
struct ShapeVertex;

class Program;

class DEVICE_EXPORT ShapePipeline {
 public:

  static const glm::vec4 kClearColor;

  ShapePipeline();
  ~ShapePipeline();

  // Uniforms.
  void set_mvp(const glm::mat4& m);
  void set_selected_mvp(const glm::mat4& m);

  // Instance Attributes.
  void set_quad_inst_attrs(const ShapeVertex* verts, GLsizei num);
  void set_tri_inst_attrs(const ShapeVertex* verts, GLsizei num);
  void set_circle_inst_attrs(const ShapeVertex* verts, GLsizei num);

  // Draw.
  void draw();

 private:
  // Initialization.
  void create_program();
  void configure_vertex_arrays();

  // Our uniform infos.
  const DefaultUniformInfo* _mvp_uniform;
  const DefaultUniformInfo* _selected_mvp_uniform;

  // Our program.
  Program* _program;

  // Our VAOs.
  VertexArray _quads_vao;
  VertexArray _tris_vao;
  VertexArray _circles_vao;

  // Our instanced geometry attributes.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;
  GLsizei _num_quads;

  TriVBO _tri_vbo;
  TriIBO _tri_ibo;
  GLsizei _num_tris;

  CircleVBO _circle_vbo;
  CircleIBO _circle_ibo;
  GLsizei _num_circles;

  // Our instance attributes.
  VertexBuffer _quad_inst_vbo;
  VertexBuffer _tri_inst_vbo;
  VertexBuffer _circle_inst_vbo;
};


}
