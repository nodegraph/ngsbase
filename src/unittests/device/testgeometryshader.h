#pragma once

#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/renderbuffer.h>
#include <base/device/unpackedbuffers/framebuffer.h>

namespace ngs {

class Program;
class Texture;

class PackedUniformBuffer;
class UniformBuffer;
class BlockUniformInfo;
class DefaultUniformInfo;

class TestGeometryShader {
 public:
  TestGeometryShader();
  virtual ~TestGeometryShader();

 private:

  void setup_pipeline();
  void setup_fbo();
  void run_pipeline();

  // Program and vertices.
  Program* _program;
  VertexArray _vao;

  // Quad geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;

  // Output buffers.
  RenderBuffer _rbo;
  FrameBuffer _fbo;

  // Textures.
  Texture* _input_texture;
  Texture* _output_texture;

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

