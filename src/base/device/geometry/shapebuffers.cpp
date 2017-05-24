#include <base/device/deviceheadersgl.h>
#include <base/device/devicedebug.h>
#include <base/device/geometry/shapebuffers.h>
#include <iostream>

namespace ngs {

QuadIBO::QuadIBO():IndexBuffer(GL_TRIANGLE_STRIP, GL_UNSIGNED_SHORT) {
  load();
}

void QuadIBO::load() {
  // Setup Indices.
  unsigned short indices[4];
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 3;
  indices[3] = 2;
  // Load the indices.
  bind();
  load(sizeof(unsigned short) * 4, indices);
}

const AttributeFormat QuadVBO::pos_attr_format = { 3, GL_FLOAT, false, sizeof(PosTexVertex), (void*) 0, 0 };
const AttributeFormat QuadVBO::tex_attr_format = { 2, GL_FLOAT, false, sizeof(PosTexVertex), (void*) (3 * sizeof(float)), 0 };

QuadVBO::QuadVBO(const glm::vec3& min, const glm::vec3& max):VertexBuffer() {
  load(min, max);
}

void QuadVBO::load(const glm::vec3& min, const glm::vec3& max) {
  PosTexVertex attrs[4];

  glm::vec3 ll = min;
  glm::vec3 lr = min;
  lr.x = max.x;

  glm::vec3 tr = max;
  glm::vec3 tl = max;
  tl.x = min.x;

  // Setup vertices.
  attrs[0].position[0] = ll[0];
  attrs[0].position[1] = ll[1];
  attrs[0].position[2] = ll[2];

  attrs[1].position[0] = lr[0];
  attrs[1].position[1] = lr[1];
  attrs[1].position[2] = lr[2];

  attrs[2].position[0] = tr[0];
  attrs[2].position[1] = tr[1];
  attrs[2].position[2] = tr[2];

  attrs[3].position[0] = tl[0];
  attrs[3].position[1] = tl[1];
  attrs[3].position[2] = tl[2];

  // Setup coordinates.
  attrs[0].tex_coord[0] = 0;
  attrs[0].tex_coord[1] = 0;

  attrs[1].tex_coord[0] = 1;
  attrs[1].tex_coord[1] = 0;

  attrs[2].tex_coord[0] = 1;
  attrs[2].tex_coord[1] = 1;

  attrs[3].tex_coord[0] = 0;
  attrs[3].tex_coord[1] = 1;

  // Bind VBO.
  bind();
  load(sizeof(PosTexVertex) * 4, &attrs[0]);
}

// ---------------------------------------------------------------------

TriIBO::TriIBO():IndexBuffer(GL_TRIANGLE_STRIP, GL_UNSIGNED_SHORT) {
  load();
}

void TriIBO::load() {
  // Setup Indices.
  unsigned short indices[3];
  indices[0] = 0;
  indices[1] = 1;
  indices[2] = 2;
  // Load the indices.
  bind();
  load(sizeof(unsigned short) * 3, &indices[0]);
}

const AttributeFormat TriVBO::pos_attr_format = { 3, GL_FLOAT, false, sizeof(PosTexVertex), (void*) 0, 0 };
const AttributeFormat TriVBO::tex_attr_format = { 2, GL_FLOAT, false, sizeof(PosTexVertex), (void*) (3 * sizeof(float)), 0 };

TriVBO::TriVBO(const glm::vec3& tip, const glm::vec3& left, const glm::vec3& right): VertexBuffer() {
  load(tip, left, right);
}

void TriVBO::load(const glm::vec3& tip, const glm::vec3& left, const glm::vec3& right) {
  PosTexVertex attrs[3];

  // Setup vertices.
  attrs[0].position[0] = tip[0];
  attrs[0].position[1] = tip[1];
  attrs[0].position[2] = tip[2];
  attrs[1].position[0] = right[0];
  attrs[1].position[1] = right[1];
  attrs[1].position[2] = right[2];
  attrs[2].position[0] = left[0];
  attrs[2].position[1] = left[1];
  attrs[2].position[2] = left[2];

  // Setup coordinates.
  attrs[0].tex_coord[0] = 0.5;
  attrs[0].tex_coord[1] = 0;
  attrs[1].tex_coord[0] = 1;
  attrs[1].tex_coord[1] = 1;
  attrs[2].tex_coord[0] = 0;
  attrs[2].tex_coord[1] = 1;

  // Bind VBO.
  bind();
  load(sizeof(PosTexVertex) * 3, &attrs[0]);
}

// ---------------------------------------------------------------------

CircleIBO::CircleIBO():IndexBuffer(GL_TRIANGLE_FAN, GL_UNSIGNED_SHORT) {
  load();
}

void CircleIBO::load() {
  // Setup Indices.
  unsigned short indices[CircleVBO::num_indices];
  for (unsigned short i = 0; i < CircleVBO::num_indices; ++i) {
    indices[i] = i;
  }

  // Load the indices;
  bind();
  load(sizeof(unsigned short) * (CircleVBO::num_indices), &indices[0]);
}

const float CircleVBO::pi = acos(-1.0f);

const AttributeFormat CircleVBO::pos_attr_format = { 3, GL_FLOAT, false, sizeof(PosTexVertex), (void*) 0, 0 };
const AttributeFormat CircleVBO::tex_attr_format = { 2, GL_FLOAT, false, sizeof(PosTexVertex), (void*) (3 * sizeof(float)), 0 };

CircleVBO::CircleVBO(const glm::vec3& center, float radius): VertexBuffer() {
  load(center, radius);
}

void CircleVBO::load(const glm::vec3& center, float radius) {
  // There num_samples+2 vertices.
  // One is the for the center, and one is a duplicate to close out the circle.
  std::vector<PosTexVertex> attrs;
  attrs.resize(num_samples+2);

  const float inc = 2.0f * pi / static_cast<float>(num_samples);
  float angle = 0.0f;
  // First record the origin of the triangle fan.
  attrs[0].position[0] = center.x;
  attrs[0].position[1] = center.y;
  attrs[0].position[2] = center.z;
  attrs[0].tex_coord[0] = 0;
  attrs[0].tex_coord[1] = 0;
  // Now record all the outer vertices of the circle.
  for (size_t i = 0; i < num_samples+1; ++i) {
    PosTexVertex &ptv = attrs[i+1];
    // Setup vertices.
    ptv.position[0] = radius * (cos(angle) - sin(angle));
    ptv.position[1] = radius * (sin(angle) + cos(angle));
    ptv.position[2] = center.z;
    // Setup coordinates.
    ptv.tex_coord[0] = 0; // bogus value for now
    ptv.tex_coord[1] = 0; // bogus value for now
    // Ready the next loop.
    angle += inc;
  }

  // Bind VBO.
  bind();
  load(sizeof(PosTexVertex) * (num_samples+2), &attrs[0]);
}

}
