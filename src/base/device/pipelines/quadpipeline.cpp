#include <base/device/pipelines/quadpipeline.h>
#include <base/memoryallocator/taggednew.h>

#include <base/device/program/program.h>
#include <base/device/program/defaultuniforminfos.h>
#include <base/device/program/attributeinfos.h>
#include <base/resources/resources.h>

#include <iostream>

namespace {
#include <base/resources/dataheaders/displayshaders_gles3.h>
}

#if ARCH == ARCH_ANDROID
#include <android/log.h>
#endif

namespace ngs {

const glm::vec4 QuadPipeline::kClearColor(3.0f/255.0f, 169.0f/255.0f, 244.0f/255.0f, 1.00 );

QuadPipeline::QuadPipeline()
    : _mvp_uniform(NULL),
      _program(NULL),
      _quad_vbo() {
  create_program();
  configure_vertex_arrays();
}

QuadPipeline::~QuadPipeline() {
  delete_ff(_program);
}

void QuadPipeline::set_mvp(const glm::mat4& m) {
  _program->get_default_uniform_infos()->set_uniform(_mvp_uniform, &m[0][0]);
}

void QuadPipeline::create_program() {
  // Find our shaders.
  std::string version;
#if (ARCH == ARCH_LINUX) || (ARCH == ARCH_MACOS) || (ARCH == ARCH_WINDOWS)
  version = "#version 330\n";
#else
  version = "#version 300 es\n";
#endif
  std::string vs = version+std::string(monitor_poly_vert_gles3);
  std::string fs = version+std::string(monitor_poly_frag_gles3);

  // Create our program.
  _program = new_ff Program(vs, fs, "");

  // Gram some uniforms.
  _mvp_uniform = _program->get_default_uniform_infos()->get_uniform_info("model_view_project");

  // Create the single instance attributes.
  {
    ShapeVertex inst;
    inst.set_state(0);
    inst.set_scale(glm::vec2(512,512));
    inst.set_rotate(0);
    inst.set_translate(glm::vec2(0,0), -100);
    inst.set_color(100, 255, 100);
    _inst_vbo.bind();
    _inst_vbo.load(sizeof(ShapeVertex), &inst);
  }

}

void QuadPipeline::configure_vertex_arrays() {
  AttributeInfos* attr_infos = _program->get_attribute_infos();
  GLuint attr_loc = -1;
  _vao.bind();

  // Quad Geometry.
  attr_loc = attr_infos->get_attribute_location("vertex");
  _vao.set_float_vertex_buffer(attr_loc, QuadVBO::pos_attr_format, &_quad_vbo);

  // Single Quad Instance Attributes.
  attr_loc = attr_infos->get_attribute_location("state");
  _vao.set_float_vertex_buffer(attr_loc, ShapeVertex::state_attr, &_inst_vbo);
  attr_loc = attr_infos->get_attribute_location("scale");
  _vao.set_float_vertex_buffer(attr_loc, ShapeVertex::scale_attr, &_inst_vbo);
  attr_loc = attr_infos->get_attribute_location("rotate");
  _vao.set_float_vertex_buffer(attr_loc, ShapeVertex::rotate_attr, &_inst_vbo);
  attr_loc = attr_infos->get_attribute_location("translate");
  _vao.set_float_vertex_buffer(attr_loc, ShapeVertex::translate_attr, &_inst_vbo);
  attr_loc = attr_infos->get_attribute_location("color");
  _vao.set_float_vertex_buffer(attr_loc, ShapeVertex::color_attr, &_inst_vbo);

}

void QuadPipeline::draw() {
  _vao.bind();
  _quad_ibo.draw_indexed();
}

}
