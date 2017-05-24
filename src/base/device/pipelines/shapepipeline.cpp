#include <base/device/pipelines/shapepipeline.h>
#include <base/memoryallocator/taggednew.h>

#include <base/device/program/program.h>
#include <base/device/program/defaultuniforminfos.h>
#include <base/device/program/attributeinfos.h>
#include <base/resources/resources.h>

namespace {
#include <base/resources/dataheaders/displayshaders_gles3.h>
}

#if ARCH == ARCH_ANDROID
#include <android/log.h>
#endif

namespace ngs {

const glm::vec4 ShapePipeline::kClearColor(3.0f/255.0f, 169.0f/255.0f, 244.0f/255.0f, 1.00 );

ShapePipeline::ShapePipeline()
    : _mvp_uniform(NULL),
      _selected_mvp_uniform(NULL),
      _program(NULL),
      _quad_vbo(),
      _tri_vbo(),
      _circle_vbo(),
      _num_quads(0),
      _num_tris(0),
      _num_circles(0) {
  create_program();
  configure_vertex_arrays();
}

ShapePipeline::~ShapePipeline() {
  delete_ff(_program);
}

void ShapePipeline::set_mvp(const glm::mat4& m) {
  _program->get_default_uniform_infos()->set_uniform(_mvp_uniform, &m[0][0]);
}

void ShapePipeline::set_selected_mvp(const glm::mat4& m) {
  _program->get_default_uniform_infos()->set_uniform(_selected_mvp_uniform, &m[0][0]);
}

void ShapePipeline::set_quad_inst_attrs(const ShapeVertex* verts, GLsizei num) {
  //std::cerr << "the number of quad instances is: " << instances.size() << "\n";
  _num_quads = num;
  if (_num_quads) {
    _quads_vao.bind();
    _quad_inst_vbo.load(sizeof(ShapeVertex)*_num_quads, verts);
  }
}

void ShapePipeline::set_tri_inst_attrs(const ShapeVertex* verts, GLsizei num) {
  //std::cerr << "the number of tri instances is: " << instances.size() << "\n";
  _num_tris = num;
  if (_num_tris) {
    _tris_vao.bind();
    _tri_inst_vbo.load(sizeof(ShapeVertex)*_num_tris, verts);
  }
}

void ShapePipeline::set_circle_inst_attrs(const ShapeVertex* verts, GLsizei num) {
  //std::cerr << "the number of circle instances is: " << instances.size() << "\n";
  _num_circles = num;
  if (_num_circles) {
    _circles_vao.bind();
    _circle_inst_vbo.load(sizeof(ShapeVertex)*_num_circles, verts);
  }
}

void ShapePipeline::create_program() {
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
  _selected_mvp_uniform = _program->get_default_uniform_infos()->get_uniform_info("model_view_project_selected");
}

void ShapePipeline::configure_vertex_arrays() {
  AttributeInfos* attr_infos = _program->get_attribute_infos();
  GLuint attr_loc = -1;
  _program->use();

  _quads_vao.bind();
  {
    attr_loc = attr_infos->get_attribute_location("vertex");
    _quads_vao.set_float_vertex_buffer(attr_loc, QuadVBO::pos_attr_format, &_quad_vbo);
    attr_loc = attr_infos->get_attribute_location("scale");
    _quads_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::scale_attr, &_quad_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("rotate");
    _quads_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::rotate_attr, &_quad_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("translate");
    _quads_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::translate_attr, &_quad_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("color");
    _quads_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::color_attr, &_quad_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("state");
    _quads_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::state_attr, &_quad_inst_vbo);
  }

  _tris_vao.bind();
  {
      attr_loc = attr_infos->get_attribute_location("vertex");
      _tris_vao.set_float_vertex_buffer(attr_loc, TriVBO::pos_attr_format, &_tri_vbo);

      attr_loc = attr_infos->get_attribute_location("scale");
      _tris_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::scale_attr, &_tri_inst_vbo);
      attr_loc = attr_infos->get_attribute_location("rotate");
      _tris_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::rotate_attr, &_tri_inst_vbo);
      attr_loc = attr_infos->get_attribute_location("translate");
      _tris_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::translate_attr, &_tri_inst_vbo);
      attr_loc = attr_infos->get_attribute_location("color");
      _tris_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::color_attr, &_tri_inst_vbo);
      attr_loc = attr_infos->get_attribute_location("state");
      _tris_vao.set_float_vertex_buffer(attr_loc,  ShapeVertex::state_attr, &_tri_inst_vbo);
  }

  _circles_vao.bind();
  {
    attr_loc = attr_infos->get_attribute_location("vertex");
    _circles_vao.set_float_vertex_buffer(attr_loc, CircleVBO::pos_attr_format, &_circle_vbo);
    attr_loc = attr_infos->get_attribute_location("scale");
    _circles_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::scale_attr, &_circle_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("rotate");
    _circles_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::rotate_attr, &_circle_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("translate");
    _circles_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::translate_attr, &_circle_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("color");
    _circles_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::color_attr, &_circle_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("state");
    _circles_vao.set_float_vertex_buffer(attr_loc, ShapeVertex::state_attr, &_circle_inst_vbo);
  }
}

void ShapePipeline::draw() {
  _quads_vao.bind();
  _quad_ibo.draw_indexed_instances(_num_quads, 0);

  _tris_vao.bind();
  _tri_ibo.draw_indexed_instances(_num_tris, 0);

  _circles_vao.bind();
  _circle_ibo.draw_indexed_instances(_num_circles, 0);
}



}
