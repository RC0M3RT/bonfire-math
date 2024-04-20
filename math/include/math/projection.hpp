#pragma once

#include <type_traits>

#include "config.hpp"
#include "matrix4.hpp"

namespace bonfire::math {

/**
 * Makes a projection matrix using right handed coordinate system and depth range between -1 to 1
 *
 * n = znear, f = zfar, l = left, r = right, t = top, b = bottom
 *
 *         | n/r   0     0    0 |
 *     M = | 0     n/b   0    0 |
 *         | 0     0     A    B |
 *         | 0     0     -1   0 |
 *
 * r = ((n * width) / height) * tan(fovy / 2)
 * b = n * tan(fovy / 2)
 * A = (f + n) / (n - f)
 * B = (2 * f * n) / (n - f)
 *
 * a = width / height
 *
 * n/r = 1 / (a * tan(fovy / 2))
 * n/b = 1 / tan(fovy / 2)
 *
 * @param aspect aspect ratio. Width devided by the height
 * @param fovy vertical field of view angle in radians
 * @param znear z near
 * @param zfar z far
 * @return projection matrix
 */
inline auto make_projection(const float aspect, const float fovy, const float znear, const float zfar, coordinate_system::RightHandedTag,
                            depth_range::NegativeOneToOneTag) -> Mat4 {

  const auto tan_half = std::tan(fovy / 2.0f);

  const auto n_r = 1.0f / (aspect * tan_half);
  const auto n_b = 1.0f / tan_half;

  const auto A = (zfar + znear) / (znear - zfar);
  const auto B = (2.0f * zfar * znear) / (znear - zfar);

  auto m = Mat4{0.0f};

  m.column(0).x = n_r;
  m.column(1).y = n_b;
  m.column(2).z = A;
  m.column(3).z = B;

  // w will contain negated z value
  m.column(2).w = -1.0f;

  return m;
}

/**
 * Makes a projection matrix using right handed coordinate system and depth range between 0 to 1
 *
 * n = znear, f = zfar, l = left, r = right, t = top, b = bottom
 *
 *         | n/r   0     0    0 |
 *     M = | 0     n/b   0    0 |
 *         | 0     0     A    B |
 *         | 0     0     -1   0 |
 *
 * r = ((n * width) / height) * tan(fovy / 2)
 * b = n * tan(fovy / 2)
 * A = f / (n - f)
 * B = (f * n) / (n - f)
 *
 * a = width / height
 *
 * n/r = 1 / (a * tan(fovy / 2))
 * n/b = 1 / tan(fovy / 2)
 *
 * @param aspect aspect ratio. Width devided by the height
 * @param fovy vertical field of view angle in radians
 * @param znear z near
 * @param zfar z far
 * @return projection matrix
 */
inline auto make_projection(const float aspect, const float fovy, const float znear, const float zfar, coordinate_system::RightHandedTag,
                            depth_range::ZeroToOneTag) -> Mat4 {

  const auto tan_half = std::tan(fovy / 2.0f);

  const auto n_r = 1.0f / (aspect * tan_half);
  const auto n_b = 1.0f / tan_half;

  const auto A = (zfar) / (znear - zfar);
  const auto B = (zfar * znear) / (znear - zfar);

  auto m = Mat4{0.0f};

  m.column(0).x = n_r;
  m.column(1).y = n_b;
  m.column(2).z = A;
  m.column(3).z = B;

  // w will contain negated z value
  m.column(2).w = -1.0f;

  return m;
}

/**
 * Makes a projection matrix using left handed coordinate system and depth range between -1 to 1
 *
 * n = znear, f = zfar, l = left, r = right, t = top, b = bottom
 *
 *         | n/r   0     0    0 |
 *     M = | 0     n/b   0    0 |
 *         | 0     0     A    B |
 *         | 0     0     -1   0 |
 *
 * r = ((n * width) / height) * tan(fovy / 2)
 * b = n * tan(fovy / 2)
 * A = (f + n) / (f - n)
 * B = (-2 * f * n) / (f - n)
 *
 * a = width / height
 *
 * n/r = 1 / (a * tan(fovy / 2))
 * n/b = 1 / tan(fovy / 2)
 *
 * @param aspect aspect ratio. Width devided by the height
 * @param fovy vertical field of view angle in radians
 * @param znear z near
 * @param zfar z far
 * @return projection matrix
 */
inline auto make_projection(const float aspect, const float fovy, const float znear, const float zfar, coordinate_system::LeftHandedTag,
                            depth_range::NegativeOneToOneTag) -> Mat4 {
  const auto tan_half = std::tan(fovy / 2.0f);

  const auto n_r = 1.0f / (aspect * tan_half);
  const auto n_b = 1.0f / tan_half;

  const auto A = (zfar + znear) / (zfar - znear);
  const auto B = (-2.0f * zfar * znear) / (zfar - znear);

  auto m = Mat4{0.0f};

  m.column(0).x = n_r;
  m.column(1).y = n_b;
  m.column(2).z = A;
  m.column(3).z = B;

  // w will contain unchanged z value
  m.column(2).w = 1.0f;

  return m;
}

/**
 * Makes a projection matrix using left handed coordinate system and depth range between 0 to 1
 *
 * n = znear, f = zfar, l = left, r = right, t = top, b = bottom
 *
 *         | n/r   0     0    0 |
 *     M = | 0     n/b   0    0 |
 *         | 0     0     A    B |
 *         | 0     0     -1   0 |
 *
 * r = ((n * width) / height) * tan(fovy / 2)
 * b = n * tan(fovy / 2)
 * A = (f) / (f - n)
 * B = (-1 * f * n) / (f - n)
 *
 * a = width / height
 *
 * n/r = 1 / (a * tan(fovy / 2))
 * n/b = 1 / tan(fovy / 2)
 *
 * @param aspect aspect ratio. Width devided by the height
 * @param fovy vertical field of view angle in radians
 * @param znear z near
 * @param zfar z far
 * @return projection matrix
 */
inline auto make_projection(const float aspect, const float fovy, const float znear, const float zfar, coordinate_system::LeftHandedTag,
                            depth_range::ZeroToOneTag) -> Mat4 {
  const auto tan_half = std::tan(fovy / 2.0f);

  const auto n_r = 1.0f / (aspect * tan_half);
  const auto n_b = 1.0f / tan_half;

  const auto A = (zfar) / (zfar - znear);
  const auto B = (-1.0f * zfar * znear) / (zfar - znear);

  auto m = Mat4{0.0f};

  m.column(0).x = n_r;
  m.column(1).y = n_b;
  m.column(2).z = A;
  m.column(3).z = B;

  // w will contain unchanged z value
  m.column(2).w = 1.0f;

  return m;
}

}  // namespace bonfire::math
