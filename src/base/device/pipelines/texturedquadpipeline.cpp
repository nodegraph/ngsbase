#include <base/device/pipelines/TexturedQuadPipeline.h>
#include <base/memoryallocator/taggednew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <base/device/program/program.h>
#include <base/device/program/defaultuniforminfos.h>
#include <base/device/program/attributeinfos.h>

#include <base/device/unpackedbuffers/texture.h>

#include <iostream>

namespace {
#include <base/device/pipelines/shaders/texturedquadshaders.h>
}

#if ARCH == ARCH_ANDROID
#include <android/log.h>
#endif

namespace ngs {

const glm::vec4 TexturedQuadPipeline::kTint(3.0f/255.0f, 169.0f/255.0f, 244.0f/255.0f, 1.00 );

TexturedQuadPipeline::TexturedQuadPipeline()
    : _program(NULL),
      _quad_vbo(glm::vec3(0, 0, -100), glm::vec3(512, 512, -100)) {
  create_program();
  configure_vertex_arrays();
}

TexturedQuadPipeline::~TexturedQuadPipeline() {
  delete_ff(_program);
}

void TexturedQuadPipeline::set_texture(Texture* tex) {
  // Bind the texture to texture unit 1.
  int tex_unit = 1;
  tex->bind(tex_unit);
  // Set the tex uniform.
  DefaultUniformInfos* dui = _program->get_default_uniform_infos();
  const DefaultUniformInfo* tex_dui = dui->get_uniform_info("tex");
  dui->set_uniform(tex_dui, &tex_unit);
}

void TexturedQuadPipeline::set_tint(const glm::vec4& color) {
  DefaultUniformInfos* dui = _program->get_default_uniform_infos();
  const DefaultUniformInfo* tc_dui = dui->get_uniform_info("tint");
  dui->set_uniform(tc_dui, &color[0]);
}

void TexturedQuadPipeline::set_mvp(const glm::mat4& mvp) {
  DefaultUniformInfos* dui = _program->get_default_uniform_infos();
  const DefaultUniformInfo* mvp_dui = dui->get_uniform_info("mvp");
  dui->set_uniform(mvp_dui, &mvp[0][0]);
}

void TexturedQuadPipeline::create_program() {
  // Create our program.
  _program = new_ff Program(textured_quad_vert, textured_quad_frag, "");

  // Set the model view project uniform.
  glm::mat4 model_view = glm::mat4(1.0);
  glm::mat4 projection = glm::ortho(0.0f, 512.0f, 0.0f, 512.0f, -1000.0f, 1000.0f);
  glm::mat4 mvp = projection * model_view;
  set_mvp(mvp);

  // Set the color.
  set_tint(kTint);
}

void TexturedQuadPipeline::configure_vertex_arrays() {
  AttributeInfos* attr_infos = _program->get_attribute_infos();
  GLuint attr_loc = -1;
  _vao.bind();

  // Quad Geometry.
  attr_loc = attr_infos->get_attribute_location("position");
  _vao.set_float_vertex_buffer(attr_loc, QuadVBO::pos_attr_format, &_quad_vbo);
  attr_loc = _program->get_attribute_infos()->get_attribute_location("tex_coord");
  _vao.set_float_vertex_buffer(attr_loc, QuadVBO::tex_attr_format, &_quad_vbo);
}

void TexturedQuadPipeline::draw() {
  _program->use();
  _vao.bind();
  _quad_ibo.draw_indexed();
}

}
