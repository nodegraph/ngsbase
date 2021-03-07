#include <base/memoryallocator/taggednew.h>
#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>
#include <base/device/geometry/attributeformat.h>
#include <base/device/pipelines/fonts/verabd_ttf.h>

#include <base/utils/simplesaver.h>
#include <base/utils/archdebug.h>

#include <base/device/program/program.h>
#include <base/device/program/defaultuniforminfos.h>
#include <base/device/program/attributeinfos.h>
//#include <base/device/geometry/distfieldtext.h>
//#include <base/device/geometry/distfieldtext.cpp>

#include <base/device/pipelines/textpipeline.h>
#include <base/device/pipelines/textures/distance_map.h>

namespace {
  #include <base/device/pipelines/shaders/textshaders_gles3.h>
}

#include <freetype-gl/texture-font.h>
#include <freetype-gl/texture-atlas.h>
#include <freetype-gl/edtaa3func.h>
#include <string.h>
#include <fstream>

namespace {

using namespace ftgl;

unsigned char *
make_distance_map( unsigned char *img,
                   unsigned int width, unsigned int height )
{
    short * xdist = (short *)  malloc( width * height * sizeof(short) );
    short * ydist = (short *)  malloc( width * height * sizeof(short) );
    double * gx   = (double *) calloc( width * height, sizeof(double) );
    double * gy      = (double *) calloc( width * height, sizeof(double) );
    double * data    = (double *) calloc( width * height, sizeof(double) );
    double * outside = (double *) calloc( width * height, sizeof(double) );
    double * inside  = (double *) calloc( width * height, sizeof(double) );
    unsigned int i;

    // Convert img into double (data)
    double img_min = 255, img_max = -255;
    for( i=0; i<width*height; ++i)
    {
        double v = img[i];
        data[i] = v;
        if (v > img_max) img_max = v;
        if (v < img_min) img_min = v;
    }
    // Rescale image levels between 0 and 1
    for( i=0; i<width*height; ++i)
    {
        data[i] = (img[i]-img_min)/img_max;
    }

    // Compute outside = edtaa3(bitmap); % Transform background (0's)
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, outside);
    for( i=0; i<width*height; ++i)
        if( outside[i] < 0 )
            outside[i] = 0.0;

    // Compute inside = edtaa3(1-bitmap); % Transform foreground (1's)
    memset(gx, 0, sizeof(double)*width*height );
    memset(gy, 0, sizeof(double)*width*height );
    for( i=0; i<width*height; ++i)
        data[i] = 1 - data[i];
    computegradient( data, width, height, gx, gy);
    edtaa3(data, gx, gy, width, height, xdist, ydist, inside);
    for( i=0; i<width*height; ++i)
        if( inside[i] < 0 )
            inside[i] = 0.0;

    // distmap = outside - inside; % Bipolar distance field
    unsigned char *out = (unsigned char *) malloc( width * height * sizeof(unsigned char) );
    for( i=0; i<width*height; ++i)
    {
        outside[i] -= inside[i];
        outside[i] = 128+outside[i]*16;
        if( outside[i] < 0 ) outside[i] = 0;
        if( outside[i] > 255 ) outside[i] = 255;
        out[i] = 255 - (unsigned char) outside[i];
        //out[i] = (unsigned char) outside[i];
    }

    free( xdist );
    free( ydist );
    free( gx );
    free( gy );
    free( data );
    free( outside );
    free( inside );
    return out;
}
}

namespace ngs {

const glm::vec4 TextPipeline::kClearColor(3.0f/255.0f, 169.0f/255.0f, 244.0f/255.0f, 1.00 );

TextPipeline::TextPipeline()
    : _program(NULL),
      _mvp_uniform(NULL),
      _selected_mvp_uniform(NULL),
      _distance_texture_uniform(NULL),
      _num_quads(0),
      _distance_map(distance_map_raw),
      _distance_map_size(distance_map_raw_len) {

  create_program();

  _atlas = ftgl::texture_atlas_new(724,724,1);
  _font = ftgl::texture_font_new_from_memory(_atlas, 96, VeraBd_ttf, VeraBd_ttf_len); // original pt_size=48

  // We create the glyphs on the system side for all the letters we would ever need.
  const char *cache = " !\"#$%&'()*+,-./0123456789:;<=>?"
                         "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
                         "`abcdefghijklmnopqrstuvwxyz{|}~";
  texture_font_load_glyphs( _font, cache );
}

TextPipeline::~TextPipeline() {
  delete_ff(_program);
}

void TextPipeline::set_mvp(const glm::mat4& m) {
  _program->get_default_uniform_infos()->set_uniform(_mvp_uniform, &m[0][0]);
}

void TextPipeline::set_selected_mvp(const glm::mat4& m) {
  _program->get_default_uniform_infos()->set_uniform(_selected_mvp_uniform, &m[0][0]);
}

void TextPipeline::set_distance_texture_unit(int texture_unit) {
  _program->get_default_uniform_infos()->set_uniform(_distance_texture_uniform, &texture_unit);
}

void TextPipeline::create_program() {

  std::string version;
#if (ARCH == ARCH_LINUX) || (ARCH == ARCH_MACOS)
  version = "#version 330\n";
#else
  version = "#version 300 es\n";
#endif
  std::string vs = version+std::string(text_vert_gles3);
  std::string fs = version+std::string(text_frag_gles3);

  // Create our program.
  _program = new_ff Program(vs, fs, "");

  _mvp_uniform = _program->get_default_uniform_infos()->get_uniform_info("model_view_project");
  _selected_mvp_uniform = _program->get_default_uniform_infos()->get_uniform_info("model_view_project_selected");
  _distance_texture_uniform = _program->get_default_uniform_infos()->get_uniform_info("distance_field");
  configure_vertex_arrays();

  // Create our distance map.
  glBindTexture(GL_TEXTURE_2D, _atlas->id);

  unsigned char *map = NULL;
  // Create our distance map dynamically.
#if BAKE_OUT_DISTANCE_MAP
    map = make_distance_map(_atlas->data, _atlas->width, _atlas->height);
  // Bake out a distance map.
    std::ofstream ofs;
    open_output_file_stream("./distance_map.raw", ofs);
    SimpleSaver ss(ofs);
    ss.save_raw(map, _atlas->width * _atlas->height * sizeof(unsigned char));
    free(map);
    map = NULL;
#endif
  // Load a prebaked distance map.
  {
    memcpy(_atlas->data, _distance_map, _distance_map_size);
  }

  // This assumes the glyphs for all the letters we would
  // ever need have been created on the system side, before
  // the device memory is initialized.
  // Technically we only need to load this texture in the root group.
  // All other groups will use the same texture.
  texture_atlas_upload(_atlas);
}



void TextPipeline::configure_vertex_arrays() {
  AttributeInfos* attr_infos = _program->get_attribute_infos();
  GLuint attr_loc = -1;
  _program->use();

  _vao.bind();
  {
    attr_loc = attr_infos->get_attribute_location("vertex");
    _vao.set_float_vertex_buffer(attr_loc, QuadVBO::pos_attr_format, &_quad_vbo);
    attr_loc = attr_infos->get_attribute_location("tex_coord");
    _vao.set_float_vertex_buffer(attr_loc, QuadVBO::tex_attr_format, &_quad_vbo);

    attr_loc = attr_infos->get_attribute_location("scale");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::scale_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("translate1");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::translation1_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("rotation");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::rotation_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("translate2");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::translation2_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("coord_s");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::coord_s_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("coord_t");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::coord_t_attr, &_inst_vbo);
    attr_loc = attr_infos->get_attribute_location("state");
    _vao.set_float_vertex_buffer(attr_loc, CharVertex::state_attr, &_inst_vbo);
  }
}

void TextPipeline::draw() {
  _vao.bind();

  // Since we are drawing in Qt's render thread and need to make sure we restore all gl state.
  // It's better if we don't enable blending for now.
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Enable texture unit zero.
  Device::enable_texture_target(0, GL_TEXTURE_2D);

  // Bind the texture to unit zero.
  glBindTexture( GL_TEXTURE_2D, _atlas->id );

  // Set the texture unit uniform.
  int texture_unit = 0;
  set_distance_texture_unit(texture_unit);

  // Now draw.
  _quad_ibo.draw_indexed_instances(_num_quads);
}

void TextPipeline::load_chars(const CharVertex* verts, size_t num_chars) {
  _num_quads = num_chars;
  _inst_vbo.bind();
  _inst_vbo.load(sizeof(CharVertex) * _num_quads, verts);
}

}
