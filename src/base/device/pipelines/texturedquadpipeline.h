#pragma once
#include <base/device/device_export.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/vertexarray.h>

namespace ngs {

class Program;
class Texture;

class DEVICE_EXPORT TexturedQuadPipeline {
 public:

  static const glm::vec4 kTint;

  TexturedQuadPipeline();
  ~TexturedQuadPipeline();

  // Configure.
  void set_texture(Texture* tex);
  void set_tint(const glm::vec4& color);
  void set_mvp(const glm::mat4& mvp);

  // Draw.
  void draw();

 private:
  // Initialization.
  void create_program();
  void configure_vertex_arrays();

  // Our program.
  Program* _program;

  // Our VAO.
  VertexArray _vao;

  // Our geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;
};


}
