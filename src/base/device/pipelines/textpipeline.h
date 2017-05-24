#pragma once
#include <base/device/device_export.h>
#include <base/device/transforms/glmhelper.h>
#include <base/device/geometry/vertices.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/vertexarray.h>


namespace ftgl {
  struct texture_font_t;
  struct texture_atlas_t;
}

namespace ngs {

class DefaultUniformInfo;
class Resources;

//template<class A>
//class DistFieldText;

class Quad;
//struct PosTexVertex;
//struct ShapeInstance;

class DEVICE_EXPORT TextPipeline {
 public:
  static const glm::vec4 kClearColor;

  TextPipeline();
  ~TextPipeline();

  // Uniforms.
  void set_mvp(const glm::mat4& m);
  void set_selected_mvp(const glm::mat4& m);

  // Instance Attributes.
  void load_chars(const CharVertex* verts, size_t num_chars);

  // Draw.
  void draw();

 private:
  // Initialization.
  void create_program();
  void configure_vertex_arrays();

  // Uniforms.
  void set_distance_texture_unit(int texture_unit);

  // Our program.
  Program* _program;

  // Our uniform infos. These are borrowed references.
  const DefaultUniformInfo* _mvp_uniform;
  const DefaultUniformInfo* _selected_mvp_uniform;
  const DefaultUniformInfo* _distance_texture_uniform;

  // Our VAO.
  VertexArray _vao;

  // Our instanced quad geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;
  GLsizei _num_quads;

  // Our instance attributes.
  VertexBuffer _inst_vbo;

  // Our text font and it's texture atlas.
  ftgl::texture_font_t *_font;
  ftgl::texture_atlas_t *_atlas;

  const unsigned char* _distance_map;
  size_t _distance_map_size;

};


}
