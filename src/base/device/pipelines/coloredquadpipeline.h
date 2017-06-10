#pragma once
#include <base/device/device_export.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/vertexarray.h>

namespace ngs {

class Program;

class DEVICE_EXPORT ColoredQuadPipeline {
 public:

  static const glm::vec4 kColor;

  ColoredQuadPipeline();
  ~ColoredQuadPipeline();

  // Configure.
  void set_random_colors(bool random) {_random_colors = random;}
  void set_color(const glm::vec4& color);
  void set_mvp(const glm::mat4& mvp);

  // Draw.
  void draw();

 private:
  // Initialization.
  void create_program();
  void configure_vertex_arrays();

  bool _random_colors;

  // Our program.
  Program* _program;

  // Our VAO.
  VertexArray _vao;

  // Our geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;
};


}
