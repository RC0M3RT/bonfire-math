#pragma once

#include <type_traits>

#include "matrix4.hpp"

namespace bonfire::math {

constexpr void make_scale(Mat4& m, const Vec3& scale) {
  /**
        | sx   0    0   0 |
    M = | 0    sy   0   0 |
        | 0    0    sz  0 |
        | 0    0    0   1 |
  */

  m.column(0).x = scale.x;
  m.column(1).y = scale.y;
  m.column(2).z = scale.z;
  m.column(3).w = 1.0f;
}

constexpr void make_translate(Mat4& m, const Vec3& translation/*position*/) {
  /**
        | 1   0   0   tx |
    M = | 0   1   0   ty |
        | 0   0   1   tz |
        | 0   0   0   1  |
  */

  m.column(3).x = translation.x;
  m.column(3).y = translation.y;
  m.column(3).z = translation.z;
  m.column(3).w = 1.0f;
}

inline void make_rotate_x(Mat4& m, const float angle) {
  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  // left handed

  /**
       | 1    0       0       0 |
  Rx = | 0    cosa    sina   0 |
       | 0    -sina    cosa    0 |
       | 0    0       0       1 |
  */

  m.column(1).y = cos_a; m.column(2).y = sin_a;
  m.column(1).z = -sin_a; m.column(2).z = cos_a;
}

inline void make_rotate_z(Mat4& m, const float angle) {
  /**
         | cosa    sina     0   0 |
    Rz = | -sina   cosa     0   0 |
         | 0       0        1   0 |
         | 0       0        0   1 |
  */

  // left handed

  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  m.column(0).x = cos_a; m.column(1).x = sin_a;
  m.column(0).y = -sin_a; m.column(1).y = cos_a;
}

inline void make_rotate_y(Mat4& m, const float angle) {
  /**
       | cosa     0    -sina     0 |
  Ry = | 0        1    0        0 |
       | sina    0     cosa     0 |
       | 0        0    0        1 |
  */

  // left handed

  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  m.column(0).x = cos_a; m.column(2).x = -sin_a; // this is inverted, see sina
  m.column(0).z = sin_a; m.column(2).z = cos_a; // this is inverted, see -sina
}

} // namespace bonfire::math

