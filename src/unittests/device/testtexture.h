#pragma once

#include <base/device/packedbuffers/elementid.h>
#include <string>

#include <base/device/transforms/glmhelper.h>

#include <functional>

namespace ngs {

/*
This test creates a packed texture, then unpacks it, then loads it onto the gpu.
Then it is read back and we check packed chunks equality operator.
 */

class Texture;
class PackedTexture;
class TexturedQuadPipeline;

class TestTexture {
 public:
	TestTexture(ElementID element_id, bool normalized_access, std::function<void()> swap);
  virtual ~TestTexture();

 private:
  void create_packed_texture();
  void create_texture();
  void read_back_texture();
  void check_read_back_texture();

  std::function<void()> _swap;

  // Determine whether we'll be testing with textures which yield normalized values or not.
  bool _normalized_access;
  ElementID _element_id;

  PackedTexture* _packed_texture;
  Texture* _texture;
  PackedTexture* _read_back_packed_texture;

  TexturedQuadPipeline* _pipeline;
};

}
