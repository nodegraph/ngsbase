#pragma once


#include <string>

#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/renderbuffer.h>
#include <base/device/unpackedbuffers/framebuffer.h>


namespace ngs {

class Program;
class Texture;

class PackedUniformBuffer;
class UniformBuffer;
class BlockUniformInfos;
class BlockUniformInfo;
class DefaultUniformInfo;

class TestMultiSampling {
 public:
  TestMultiSampling();
  virtual ~TestMultiSampling();

 private:
  void setup_multisample_fbo();
  void check_sample_positions();
  void setup_blit_fbo();
  void check_blit_texture(float first_row_value, float second_row_value);

  // Non-centroid based shaders.
  void setup_pipeline();
  void setup_quad();
  void run_pipeline();

  // Centroid based shaders.
  void setup_centroid_quad();
  void setup_centroid_pipeline();
  void run_centroid_pipeline();

  // Quad geometry.
  QuadVBO* _quad_vbo;
  QuadIBO _quad_ibo;

  // Program.
  Program* _program;  // Pipeline which doesn't use "centroid out" for the tex coord.
  Program* _centroid_program;  // Pipeline which uses "centroid out" for the tex coord.
  Texture* _input_texture;
  VertexArray _vao;

  // The multi-sampled render setup.
  FrameBuffer _fbo;  // Used for multi-sampled rendering.
  RenderBuffer _depth_stencil_rbo;  // Multi-sampled depth/stencil.
  RenderBuffer _color_rbo;  // Multi-sampled output.

  // The destination for blitting of the multi-sampled result from above.
  FrameBuffer _blit_fbo;  // Use to coalesce the multi-samples down to one color per pixel.
  Texture* _blit_texture;  // Final output.

  // Uniform Buffers.
  PackedUniformBuffer* _setup_pubo;
  UniformBuffer* _setup_ubo;

  // Info about our default uniforms.
  const DefaultUniformInfo* _image_texture_info;

  // Info about our block uniforms.
  const BlockUniformInfo* _model_view_projection_info;
  const BlockUniformInfo* _tint_color_info;
};

}

