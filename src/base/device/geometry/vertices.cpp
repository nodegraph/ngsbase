#include <base/device/deviceheadersgl.h>
#include <base/device/geometry/vertices.h>
#include <base/device/unpackedbuffers/vertexbuffer.h>

namespace ngs {

// ---------------------------------------------------------------------------------------------------------------------------------------------

const AttributeFormat PosTexVertex::position_attr = {3, GL_FLOAT, false, sizeof(PosTexVertex), 0, 0};
const AttributeFormat PosTexVertex::tex_coord_attr = {2, GL_FLOAT, false, sizeof(PosTexVertex), (void*) (3 * sizeof(float)), 0};

// ---------------------------------------------------------------------------------------------------------------------------------------------

const AttributeFormat ShapeVertex::scale_attr = { 2, GL_FLOAT, false, sizeof(ShapeVertex), (void*) (0), 1};
const AttributeFormat ShapeVertex::rotate_attr = { 1, GL_FLOAT, false, sizeof(ShapeVertex), (void*) (2 * sizeof(float)), 1};
const AttributeFormat ShapeVertex::translate_attr = { 3, GL_FLOAT, false, sizeof(ShapeVertex), (void*) (3 * sizeof(float)), 1};
const AttributeFormat ShapeVertex::color_attr = { 3, GL_UNSIGNED_BYTE, true, sizeof(ShapeVertex), (void*) (6 * sizeof(float)), 1};
const AttributeFormat ShapeVertex::state_attr = { 1, GL_UNSIGNED_BYTE, false, sizeof(ShapeVertex), (void*) (6 * sizeof(float) + 3 * sizeof(unsigned char)), 1};

void ShapeVertex::set_scale(const glm::vec2& s) {
  scale[0] = s.x;
  scale[1] = s.y;
}

void ShapeVertex::set_scale(float sx, float sy) {
  scale[0] = sx;
  scale[1] = sy;
}

void ShapeVertex::set_rotate(float r) {
  rotate = r;
}

void ShapeVertex::set_translate(const glm::vec2& t, float z) {
  translate[0] = t.x;
  translate[1] = t.y;
  translate[2] = z;
}

void ShapeVertex::set_translate(float tx, float ty, float tz) {
  translate[0] = tx;
  translate[1] = ty;
  translate[2] = tz;
}

void ShapeVertex::set_color(const std::array<unsigned char,4>& c) {
  color[0] = c[0];
  color[1] = c[1];
  color[2] = c[2];
}

void ShapeVertex::set_color(unsigned char r, unsigned char g, unsigned char b) {
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

void ShapeVertex::set_state(unsigned char s) {
  state = s;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------

const AttributeFormat CharVertex::scale_attr = { 2, GL_FLOAT, false, sizeof(CharVertex), (void*) (0), 1 };
const AttributeFormat CharVertex::translation1_attr = { 2, GL_FLOAT, false, sizeof(CharVertex), (void*) (2 * sizeof(float)), 1 };
const AttributeFormat CharVertex::rotation_attr = { 1, GL_FLOAT, false, sizeof(CharVertex), (void*) (4 * sizeof(float)), 1 };
const AttributeFormat CharVertex::translation2_attr = { 2, GL_FLOAT, false, sizeof(CharVertex), (void*) (5 * sizeof(float)), 1 };
const AttributeFormat CharVertex::coord_s_attr = { 2, GL_FLOAT, false, sizeof(CharVertex), (void*) (7 * sizeof(float)), 1 };
const AttributeFormat CharVertex::coord_t_attr = { 2, GL_FLOAT, false, sizeof(CharVertex), (void*) (9 * sizeof(float)), 1 };
const AttributeFormat CharVertex::state_attr = { 1, GL_UNSIGNED_BYTE, false, sizeof(CharVertex), (void*) (11 * sizeof(float)), 1 };


void CharVertex::set_scale(float sx, float sy) {
  scale[0] = sx;
  scale[1] = sy;
}

void CharVertex::set_translate1(float x, float y) {
  translate1[0] = x;
  translate1[1] = y;
}

void CharVertex::set_translate1(const glm::vec2& t1) {
  translate1[0] = t1.x;
  translate1[1] = t1.y;
}

void CharVertex::set_rotate(float r) {
  rotate = r;
}

void CharVertex::set_translate2(float x, float y) {
  translate2[0] = x;
  translate2[1] = y;
}

void CharVertex::set_translate2(const glm::vec2& t2) {
  translate2[0] = t2.x;
  translate2[1] = t2.y;
}

void CharVertex::set_coord_s(float min_s, float max_s) {
  coord_s[0] = min_s;
  coord_s[1] = max_s;
}

void CharVertex::set_coord_t(float min_t, float max_t) {
  coord_t[0] = min_t;
  coord_t[1] = max_t;
}

void CharVertex::set_state(unsigned char s) {
  state = s;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------

}
