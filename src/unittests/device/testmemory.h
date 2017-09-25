#pragma once

#include <functional>

namespace ngs {

class Game;
class ColoredQuadPipeline;
class RenderBuffer;

class TestMemory {
 public:
  TestMemory(std::function<void()> swap);
  virtual ~TestMemory();

  void draw_quad();
  RenderBuffer* create_depth_rbo(int width, int height);
  void rundown_memory_with_depth_textures(int num);
  void rundown_memory_with_depth_rbos(int num);
  void rundown_memory_with_textures(int num);
 private:
  std::function<void()> _swap;

  static const int _width = 1024;//512;
  static const int _height = 1024;//512;
  static const int _min_gpu_mem = 300000;  // This is in kbytes.

  ColoredQuadPipeline* _pipeline;
};

}
