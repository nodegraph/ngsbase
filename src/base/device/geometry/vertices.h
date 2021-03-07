#pragma once
#include <base/device/device_export.h>
#include <base/device/devicebasictypesgl.h>
#include <base/device/geometry/attributeformat.h>
#include <base/device/transforms/glmhelper.h>
#include <vector>
#include <array>

namespace ngs {

static const unsigned char hidden_bitmask = 16;
static const unsigned char selected_transform_bitmask = 1;
static const unsigned char selected_color_bitmask = 2;


struct DEVICE_EXPORT PosTexVertex {
  float position[3];
  float tex_coord[2];

  static const AttributeFormat position_attr;
  static const AttributeFormat tex_coord_attr;
};


struct DEVICE_EXPORT ShapeVertex {
  float scale[2]; // appears as vec2 in glsl
  float rotate;
  float translate[3]; // appears as vec3 in glsl
  unsigned char color[3]; // appears as vec3 in glsl
  unsigned char state; // appears as uint in glsl
  // total byes = 2*4 + 4 + 3*4 + 3 + 1 = 28;

  static const AttributeFormat scale_attr;
  static const AttributeFormat rotate_attr;
  static const AttributeFormat translate_attr;
  static const AttributeFormat color_attr;
  static const AttributeFormat state_attr;

  void set_scale(const glm::vec2& s);
  void set_scale(float sx, float sy);
  void set_rotate(float r);
  void set_translate(const glm::vec2& t, float z);
  void set_translate(float tx, float ty, float tz);
  void set_color(const std::array<unsigned char, 4>& c);
  void set_color(unsigned char r, unsigned char g, unsigned char b);
  void set_state(unsigned char s);
};

struct DEVICE_EXPORT CharVertex {
  float scale[2];
  float translate1[2];
  float rotate;
  float translate2[2];
  float coord_s[2]; // min and max for s
  float coord_t[2]; // min and max for t
  unsigned char state;

  static const AttributeFormat scale_attr;
  static const AttributeFormat translation1_attr;
  static const AttributeFormat rotation_attr;
  static const AttributeFormat translation2_attr;
  static const AttributeFormat coord_s_attr;
  static const AttributeFormat coord_t_attr;
  static const AttributeFormat state_attr;

  void set_scale(float sx, float sy);
  void set_translate1(float x, float y);
  void set_translate1(const glm::vec2& t1);
  void set_rotate(float r);
  void set_translate2(float x, float y);
  void set_translate2(const glm::vec2& t2);
  void set_coord_s(float min_s, float max_s);
  void set_coord_t(float min_t, float max_t);
  void set_state(unsigned char s);
};

}
