#pragma once
#include <base/device/device_export.h>
#include <base/device/geometry/vertices.h>
#include <base/device/transforms/glmhelper.h>
#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/unpackedbuffers/vertexbuffer.h>
#include <base/device/unpackedbuffers/indexbuffer.h>
#include <vector>


namespace ngs {

class DEVICE_EXPORT TextIBO: public IndexBuffer {
 public:
  TextIBO(unsigned int num_quads);
 private:
  using IndexBuffer::load;
  void load(unsigned int num_quads);
};

class DEVICE_EXPORT TextVBO : public VertexBuffer {
 public:
  static const AttributeFormat pos_attr_format;
  static const AttributeFormat tex_attr_format;
  TextVBO(const PosTexVertex* verts, unsigned int num_quads); // There should be 4 verts per quad.
 private:
};


}


