#pragma once
#include <base/device/device_export.h>
#include <base/device/devicebasictypesgl.h>
#include <base/device/geometry/vertices.h>
#include <base/device/transforms/glmhelper.h>
#include <base/device/unpackedbuffers/vertexarray.h>
#include <base/device/unpackedbuffers/vertexbuffer.h>
#include <base/device/unpackedbuffers/indexbuffer.h>
#include <vector>


namespace ngs {

/*
 * The Quad is draw with the lower left at min
 * and the upper right at max.
 */

class DEVICE_EXPORT QuadIBO: public IndexBuffer {
 public:
  QuadIBO();
 private:
  using IndexBuffer::load;
  void load();
};

class DEVICE_EXPORT QuadVBO : public VertexBuffer {
 public:
  static const AttributeFormat pos_attr_format;
  static const AttributeFormat tex_attr_format;
  QuadVBO(const glm::vec3& min = glm::vec3(0, 0, 0), const glm::vec3& max = glm::vec3(1, 1, 0));
 private:
  using VertexBuffer::load;
  void load(const glm::vec3& min, const glm::vec3& max);
};

/*
 * The triangle is drawn as follows.
 *
 *        left . |width| . right
 *               ______    ==
 *               \    /    |
 *                \  /     |  height
 *                 \/      |
 *                  ^      ==
 *                 tip
 *
 */

class DEVICE_EXPORT TriIBO: public IndexBuffer {
 public:
  TriIBO();
 private:
  using IndexBuffer::load;
  void load();
};

class DEVICE_EXPORT TriVBO : public VertexBuffer {
 public:
  static const AttributeFormat pos_attr_format;
  static const AttributeFormat tex_attr_format;
  TriVBO(const glm::vec3& tip = glm::vec3(0, 0, 0), const glm::vec3& left = glm::vec3(-1, 1, 0), const glm::vec3& right = glm::vec3(1, 1, 0));
 private:
  using VertexBuffer::load;
  void load(const glm::vec3& tip, const glm::vec3& left, const glm::vec3& right);
};

/*
 * The Circle is drawn with radius r and origin o.
 */

class DEVICE_EXPORT CircleIBO: public IndexBuffer {
 public:
  CircleIBO();
 private:
  using IndexBuffer::load;
  void load();
};

class DEVICE_EXPORT CircleVBO: public VertexBuffer {
 public:
  static const AttributeFormat pos_attr_format;
  static const AttributeFormat tex_attr_format;
  static const size_t num_samples = 12;
  static const size_t num_indices = 14;
  static const float pi;
  CircleVBO(const glm::vec3& center = glm::vec3(0,0,0), float radius = 1.0f);
 private:
  using VertexBuffer::load;
  void load(const glm::vec3& center, float radius);
};


}

