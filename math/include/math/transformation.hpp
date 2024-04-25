#pragma once

#include <type_traits>

#include "config.hpp"

#include "matrix4.hpp"

namespace bonfire::math {

constexpr auto make_scale(const float3& scale) -> Mat4 {
  /**
        | sx   0    0   0 |
    M = | 0    sy   0   0 |
        | 0    0    sz  0 |
        | 0    0    0   1 |
  */

  auto m = Mat4::identity();

  m.column(0).x = scale.x;
  m.column(1).y = scale.y;
  m.column(2).z = scale.z;
  m.column(3).w = 1.0f;

  return m;
}

constexpr auto make_translate(const float3& position) -> Mat4 {
  /**
        | 1   0   0   tx |
    M = | 0   1   0   ty |
        | 0   0   1   tz |
        | 0   0   0   1  |
  */

  auto m = Mat4::identity();

  m.column(3).x = position.x;
  m.column(3).y = position.y;
  m.column(3).z = position.z;
  m.column(3).w = 1.0f;

  return m;
}

inline auto make_rotate_x(const float angle) -> Mat4 {
  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  /**
       | 1    0       0        0 |
  Rx = | 0    cosa    -sina    0 |
       | 0    sina    cosa     0 |
       | 0    0       0        1 |
  */

  auto m = Mat4::identity();

  m.column(1).y = cos_a; m.column(2).y = -sin_a;
  m.column(1).z = sin_a; m.column(2).z = cos_a;

  return m;
}

inline auto make_rotate_z(const float angle) -> Mat4 {
  /**
         | cosa    -sina    0   0 |
    Rz = | sina   cosa      0   0 |
         | 0       0        1   0 |
         | 0       0        0   1 |
  */

  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  auto m = Mat4::identity();

  m.column(0).x = cos_a; m.column(1).x = -sin_a;
  m.column(0).y = sin_a; m.column(1).y = cos_a;

  return m;
}

inline auto make_rotate_y(const float angle) -> Mat4 {
  /**
       | cosa     0    sina     0 |
  Ry = | 0        1    0        0 |
       | -sina    0    cosa     0 |
       | 0        0    0        1 |
  */

  const auto cos_a = std::cos(angle);
  const auto sin_a = std::sin(angle);

  auto m = Mat4::identity();

  m.column(0).x = cos_a; m.column(2).x = sin_a;
  m.column(0).z = -sin_a; m.column(2).z = cos_a;

  return m;
}

inline auto make_world_matrix(const float3& scale, const float3& rotation, const float3& position) -> Mat4 {
  const auto scale_matrix = make_scale(scale);

  const auto translation_matrix = make_translate(position);

  const auto rotation_matrix_x = make_rotate_x(rotation.x);
  const auto rotation_matrix_y = make_rotate_y(rotation.y);
  const auto rotation_matrix_z = make_rotate_z(rotation.z);

  return translation_matrix * rotation_matrix_y * rotation_matrix_x * rotation_matrix_z * scale_matrix;
}

} // namespace bonfire::math

