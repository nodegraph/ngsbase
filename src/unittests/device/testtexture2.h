#pragma once

#include <base/device/packedbuffers/elementid.h>
#include <string>

#include <base/device/transforms/glmhelper.h>

namespace ngs {

/*
This test creates a packed texture, then unpacks it, then loads it onto the gpu.
Then it is read back and we check packed chunks equality operator.
 */

class Texture;
class PackedTexture;

class TestTexture2 {
 public:
	TestTexture2(ElementID element_id, bool normalized_access);
  virtual ~TestTexture2();

 private:
  void create_packed_texture();
  void create_texture();
  void read_back_texture();
  void check_read_back_texture();

  // Determine whether we'll be testing with textures which yield normalized values or not.
  bool _normalized_access;
  ElementID _element_id;

  PackedTexture* _packed_texture;
  Texture* _texture;
  PackedTexture* _read_back_packed_texture;
};

}
