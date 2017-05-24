#include "testmemory.h"
#include <base/memoryallocator/taggednew.h>
#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>

// Unpacked.
#include <base/device/unpackedbuffers/texture.h>
#include <base/device/unpackedbuffers/renderbuffer.h>
#include <base/device/unpackedbuffers/framebuffer.h>

// Pipelines.
#include <base/device/pipelines/quadpipeline.h>


#include <iostream>
#include <limits>
#include <vector>

namespace {
GLint get_total_mem() {
#if GLES_MAJOR_VERSION >= 100
  GLint total_kb;
  gpu(glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &total_kb));
  return total_kb;
}
GLint get_available_mem() {
  GLint available_kb;
  gpu(glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &available_kb));
  return available_kb;
}
#endif
}

namespace ngs {

TestMemory::TestMemory():
    _pipeline(new_ff QuadPipeline()) {
  rundown_memory_with_depth_textures(100);
  rundown_memory_with_depth_rbos(100);
  rundown_memory_with_textures(100);
}

TestMemory::~TestMemory() {
  delete_ff(_pipeline);
}

void TestMemory::draw_quad() {
  _pipeline->draw();
}

RenderBuffer* TestMemory::create_depth_rbo(int width, int height) {
  // Render buffer objects fail during storage creation when the gpu memory is around 300MB.
  // You should prefer to use regular textures instead.
  return new_ff RenderBuffer(GL_DEPTH32F_STENCIL8, width, height);
}

void TestMemory::rundown_memory_with_depth_textures(int num) {
  std::vector<FrameBuffer*> fbos;
  std::vector<Texture*> depth_textures;
  std::vector<Texture*> textures;

  // Allocate almost all of the gpu memory.
  for (int i=0; i<num; ++i) {
    // Create our depth texture.
    Texture* depth_texture = create_depth_stencil_texture(0, _width, _height);
    depth_textures.push_back(depth_texture);

    // Create our fbo.
    FrameBuffer* fbo = new_ff FrameBuffer();
    fbos.push_back(fbo);
    fbo->bind();

    // Create our texture.
    Texture* texture = new_ff Texture(0, FloatElement, _width, _height, 4, false);
    textures.push_back(texture);

    // Attach our depth buffer.
    //fbo->attach_texture(GL_DEPTH_STENCIL_ATTACHMENT,*depth_texture,0);
    fbo->attach_texture(GL_DEPTH_ATTACHMENT, *depth_texture, 0);

    // Attach our stencil buffer.
    fbo->attach_texture(GL_STENCIL_ATTACHMENT, *depth_texture, 0);

    // Attach the texture to the fbo.
    fbo->attach_texture(GL_COLOR_ATTACHMENT0, *texture, 0);

    assert(fbo->is_complete());

    // Clear the color buffer.
    gpu(glClearColor(1, 0, 0, 1));
    gpu(glClear(GL_COLOR_BUFFER_BIT));

    // Clear depth buffer.
    gpu(glClearDepthf(1.0f));
    gpu(glClearDepthf((float)i/1000000.0f));

    draw_quad();

    // Unbind the fbo.
    fbo->unbind();

#if GLES_MAJOR_VERSION >= 100
    std::cerr << "DepthTexture #" << i << " Total KB: "<<get_total_mem()<<"  Available KB: "<<get_available_mem()<<"\n";
#endif
  }

  // Cleanup
  for (size_t i = 0; i < textures.size(); i++) {
    delete_ff(textures[i]);
    delete_ff(depth_textures[i]);
    delete_ff(fbos[i]);
  }
}

void TestMemory::rundown_memory_with_depth_rbos(int num) {
  std::vector<FrameBuffer*> fbos;
  std::vector<RenderBuffer*> rbos;
  std::vector<Texture*> textures;

  GLint total_kb = 0;
  GLint available_kb = 0;

  // Allocate almost all of the gpu memory.
  for (int i=0; i<num; ++i) {

    // Create our depth texture.
    RenderBuffer* rbo = create_depth_rbo(_width, _height);
    rbos.push_back(rbo);

    // Create our fbo.
    FrameBuffer* fbo = new_ff FrameBuffer();
    fbos.push_back(fbo);
    fbo->bind();

    // Attach depth buffer.
    fbo->attach_render_buffer(GL_DEPTH_ATTACHMENT, *rbo);

    // Attach stencil buffer.
    fbo->attach_render_buffer(GL_STENCIL_ATTACHMENT, *rbo);
    // Create our texture.
    Texture* texture = new_ff Texture(0, FloatElement, _width, _height, 4, false);
    textures.push_back(texture);

    // Attach the texture to the fbo.
    fbo->attach_texture(GL_COLOR_ATTACHMENT0, *texture, 0);

    assert(fbo->is_complete());

    // Clear the color buffer.
    gpu(glClearColor(1, 0, 0, 1));
    gpu(glClear(GL_COLOR_BUFFER_BIT));

    // Clear depth buffer.
    gpu(glClearDepthf((float)i/1000000.0f));
    gpu(glClear(GL_DEPTH_BUFFER_BIT));

    draw_quad();

    // Unbind the fbo.
    fbo->unbind();

#if GLES_MAJOR_VERSION >= 100
    std::cerr << "DepthRBO #" << i << " Total KB: "<<get_total_mem()<<"  Available KB: "<<get_available_mem()<<"\n";
#endif

  }

  // Cleanup.
  for (size_t i = 0; i < textures.size(); i++) {
    delete_ff(textures[i]);
    delete_ff(rbos[i]);
    delete_ff(fbos[i]);
  }
}

void TestMemory::rundown_memory_with_textures(int num) {
  std::vector<Texture*> textures;

  GLint total_kb = 0;
  GLint available_kb = 0;

  FrameBuffer* fbo = new_ff FrameBuffer();

  // Allocate almost all of the gpu memory.
  // Note gpu won't really allocate unless we use it somehow in fbo.
  for (int i=0; i<num; ++i) {
    fbo->bind();

    // Create our texture.
    Texture* texture = new_ff Texture(0, FloatElement, _width, _height, 4, false);
    assert(texture);
    textures.push_back(texture);

    fbo->attach_texture(GL_COLOR_ATTACHMENT0, *texture, 0);

    assert(fbo->is_complete());

    // Clear the color buffer.
    gpu(glClearColor(1, 0, 0, 1));
    gpu(glClear(GL_COLOR_BUFFER_BIT));

    // Clear depth buffer.
    gpu(glClearDepthf((float)i/1000000.0f));
    gpu(glClear(GL_DEPTH_BUFFER_BIT));

    draw_quad();

    fbo->unbind();

#if GLES_MAJOR_VERSION >= 100
    std::cerr << "Texture #" << i << " Total KB: "<<get_total_mem()<<"  Available KB: "<<get_available_mem()<<"\n";
#endif
  }

  // Cleanup.
  for (size_t i = 0; i < textures.size(); i++) {
    // Delete our texture.
    delete_ff(textures[i]);
  }
  delete_ff(fbo);
}

}
