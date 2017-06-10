#include <base/device/pipelines/coloredquadpipeline.h>
#include <base/memoryallocator/taggednew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <base/device/program/program.h>
#include <base/device/program/defaultuniforminfos.h>
#include <base/device/program/attributeinfos.h>

#include <iostream>

namespace {
#include <base/device/pipelines/shaders/coloredquadshaders.h>
}

#if ARCH == ARCH_ANDROID
#include <android/log.h>
#endif

namespace ngs {

const glm::vec4 ColoredQuadPipeline::kColor(3.0f/255.0f, 169.0f/255.0f, 244.0f/255.0f, 1.00 );

ColoredQuadPipeline::ColoredQuadPipeline()
    : _random_colors(true),
      _program(NULL),
      _quad_vbo(glm::vec3(0,0,-100), glm::vec3(512,512,-100)) {
  create_program();
  configure_vertex_arrays();
}

ColoredQuadPipeline::~ColoredQuadPipeline() {
  delete_ff(_program);
}

void ColoredQuadPipeline::set_color(const glm::vec4& color) {
  DefaultUniformInfos* dui = _program->get_default_uniform_infos();
  const DefaultUniformInfo* tc_dui = dui->get_uniform_info("color");
  dui->set_uniform(tc_dui, &color[0]);
}

void ColoredQuadPipeline::set_mvp(const glm::mat4& mvp) {
  DefaultUniformInfos* dui = _program->get_default_uniform_infos();
  const DefaultUniformInfo* mvp_dui = dui->get_uniform_info("mvp");
  dui->set_uniform(mvp_dui, &mvp[0][0]);
}

void ColoredQuadPipeline::create_program() {
  // Create our program.
  _program = new_ff Program(colored_quad_vert, colored_quad_frag, "");

  // Set the model view project uniform.
  glm::mat4 model_view = glm::mat4(1.0);
  glm::mat4 projection = glm::ortho(0.0f, 512.0f, 0.0f, 512.0f, -1000.0f, 1000.0f);
  glm::mat4 mvp = projection * model_view;
  set_mvp(mvp);

  // Set the color.
  set_color(kColor);
}

void ColoredQuadPipeline::configure_vertex_arrays() {
  AttributeInfos* attr_infos = _program->get_attribute_infos();
  GLuint attr_loc = -1;
  _vao.bind();

  // Quad Geometry.
  attr_loc = attr_infos->get_attribute_location("position");
  _vao.set_float_vertex_buffer(attr_loc, QuadVBO::pos_attr_format, &_quad_vbo);
}

void ColoredQuadPipeline::draw() {
  _program->use();

  // Randomize colors according to setting.
  if (_random_colors) {
    float r = (float) rand() / (float) RAND_MAX;
    float g = (float) rand() / (float) RAND_MAX;
    float b = (float) rand() / (float) RAND_MAX;
    glm::vec4 color(r, g, b, 1.0f);
    set_color(color);
  }
  _vao.bind();
  _quad_ibo.draw_indexed();
}

}
