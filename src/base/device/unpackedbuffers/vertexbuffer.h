#pragma once
#include <base/device/device_export.h>
#include <base/device/unpackedbuffers/buffer.h>

namespace ngs {


class DEVICE_EXPORT VertexBuffer : public Buffer {
 public:
  VertexBuffer();
  virtual ~VertexBuffer();
};

}
