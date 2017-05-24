#pragma once

#include <base/device/asyncquery.h>
#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/geometry/shapebuffers.h>
#include <base/device/unpackedbuffers/renderbuffer.h>
#include <base/device/unpackedbuffers/framebuffer.h>

namespace ngs {

class Program;
class Texture;

class BlockUniformInfos;
class PackedUniformBuffer;
class UniformBuffer;
class BlockUniformInfo;

class TestAsyncQuery {
 public:
  TestAsyncQuery();
  virtual ~TestAsyncQuery();

 private:

  void setup_pipeline();
  void setup_fbo();
  void run_pipeline();

  // Program and vertices.
  Program* _program;
  VertexArray _vao;

  // Query.
  AsyncQuery _query;

  // Quad geometry.
  QuadVBO _quad_vbo;
  QuadIBO _quad_ibo;

  // Output buffers.
  RenderBuffer _rbo;
  FrameBuffer _fbo;

  // Textures.
  Texture* _output_texture;

  // Uniform Buffers.
  PackedUniformBuffer* _setup_pubo;
  UniformBuffer* _setup_ubo;

  // Info about our block uniforms.
  const BlockUniformInfo* _model_view_projection_info;
  const BlockUniformInfo* _tint_color_info;


};

}

