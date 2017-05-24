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

class DEVICE_EXPORT QuadPipeline {
 public:

  static const glm::vec4 kClearColor;

  QuadPipeline();
  ~QuadPipeline();

  // Uniforms.
  void set_mvp(const glm::mat4& m);

  // Draw.
  void draw();

 private:
  // Initialization.
  void create_program();
  void configure_vertex_arrays();

  // Our uniform infos.
  const DefaultUniformInfo* _mvp_uniform;

  // Our program.
  Program* _program;

  // Our VAO.
  VertexArray _vao;

  // Our geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;

  // Our instances.
  VertexBuffer _inst_vbo;
};


}
