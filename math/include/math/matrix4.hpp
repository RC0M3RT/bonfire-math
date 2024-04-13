#pragma once

#include <cassert>

#include "vector4.hpp"

namespace bonfire::math {

namespace detail {

/**
 * Column-major order 4 dimentional matrix
 */
template<typename T> requires std::is_floating_point_v<T>
struct Matrix4 {
  /**
   * @brief Zero initialize matrix
   */
  constexpr Matrix4() noexcept : mat_{} {}

  /**
   * @brief Construct a matrix while initializing all members to given val
   */
  constexpr explicit Matrix4(T val) noexcept : mat_{Vector4<T>{val}, Vector4<T>{val}, Vector4<T>{val}, Vector4<T>{val}} {}

  /**
   * @brief Per member initialize matrix
   */
  constexpr explicit Matrix4(T p0x, T p0y, T p0z, T p0w, T p1x, T p1y, T p1z, T p1w, T p2x, T p2y, T p2z, T p2w, T p3x, T p3y, T p3z, T p3w) noexcept
      : mat_{Vector4<T>{p0x, p0y, p0z, p0w}, Vector4<T>{p1x, p1y, p1z, p1w}, Vector4<T>{p2x, p2y, p2z, p2w}, Vector4<T>{p3x, p3y, p3z, p3w}} {}

  /**
   * @brief Construct a matrix from 4 vector3
   */
  constexpr explicit Matrix4(const Vector3<T>& v0, T pw0, const Vector3<T>& v1, T pw1, const Vector3<T>& v2, T pw2, const Vector3<T>& v3, T pw3) noexcept
      : mat_{Vector4<T>{v0, pw0}, Vector4<T>{v1, pw1}, Vector4<T>{v2, pw2}, Vector4<T>{v3, pw3}} {}

  /**
   * @brief Construct a matrix from 4 vector4
   */
  constexpr explicit Matrix4(const Vector4<T>& v0, const Vector4<T>& v1, const Vector4<T>& v2, const Vector4<T>& v3) noexcept : mat_{v0, v1, v2, v3} {}

  constexpr static auto identity() -> Matrix4<T> {
    return Matrix4<T>{
      T{1.0f}, T{0.0f}, T{0.0f}, T{0.0f},
      T{0.0f}, T{1.0f}, T{0.0f}, T{0.0f},
      T{0.0f}, T{0.0f}, T{1.0f}, T{0.0f},
      T{0.0f}, T{0.0f}, T{0.0f}, T{1.0f}
    };
  }

  constexpr auto operator==(const Matrix4<T>& other) const noexcept -> bool {
    return mat_[0] == other.mat_[0] && mat_[1] == other.mat_[1] && mat_[2] == other.mat_[2] && mat_[3] == other.mat_[3];
  }

  constexpr auto column(std::size_t column_index) noexcept -> Vector4<T>& {
    assert(column_index < 4 && "Column index has to be smaller than 4 for 4x4 matrix");
    return mat_[column_index];
  }

  constexpr auto column(std::size_t column_index) const noexcept -> const Vector4<T>& {
    assert(column_index < 4 && "Column index has to be smaller than 4 for 4x4 matrix");
    return mat_[column_index];
  }

private:
  Vector4<T> mat_[4];
};

template<typename T>
constexpr auto operator+(const Matrix4<T>& m, const Matrix4<T>& n) noexcept -> Matrix4<T> {
  return Matrix4<T>{m.column(0) + n.column(0), m.column(1) + n.column(1), m.column(2) + n.column(2), m.column(3) + n.column(3)};
}

template<typename T>
constexpr auto operator-(const Matrix4<T>& m, const Matrix4<T>& n) noexcept -> Matrix4<T> {
  return Matrix4<T>{m.column(0) - n.column(0), m.column(1) - n.column(1), m.column(2) - n.column(2), m.column(3) - n.column(3)};
}

template<typename T>
constexpr auto operator*(const Matrix4<T>& m, T val) noexcept -> Matrix4<T> {
  return Matrix4<T>{m.column(0) * val, m.column(1) * val, m.column(2) * val, m.column(3) * val};
}

template<typename T>
constexpr auto operator/(const Matrix4<T>& m, T val) noexcept -> Matrix4<T> {
  return Matrix4<T>{m.column(0) / val, m.column(1) / val, m.column(2) / val, m.column(3) / val};
}

template<typename T>
constexpr auto operator*(const Matrix4<T>& m, const Matrix4<T>& n) noexcept -> Matrix4<T> {
  /**
        | m00(x)   m10(x)   m20(x)   m30(x) |
    M = | m01(y)   m11(y)   m21(y)   m31(y) |
        | m02(z)   m12(z)   m22(z)   m32(z) |
        | m03(w)   m13(w)   m23(w)   m33(w) |
  */
  const auto& m00 = m.column(0).x;  const auto& m10 = m.column(1).x; const auto& m20 = m.column(2).x; const auto& m30 = m.column(3).x;
  const auto& m01 = m.column(0).y;  const auto& m11 = m.column(1).y; const auto& m21 = m.column(2).y; const auto& m31 = m.column(3).y;
  const auto& m02 = m.column(0).z;  const auto& m12 = m.column(1).z; const auto& m22 = m.column(2).z; const auto& m32 = m.column(3).z;
  const auto& m03 = m.column(0).w;  const auto& m13 = m.column(1).w; const auto& m23 = m.column(2).w; const auto& m33 = m.column(3).w;

  /**
        | n00(x)   n10(x)   n20(x)   n30(x) |
    N = | n01(y)   n11(y)   n21(y)   n31(y) |
        | n02(z)   n12(z)   n22(z)   n32(z) |
        | n03(w)   n13(w)   n23(w)   n33(w) |
  */
  const auto& n00 = n.column(0).x;  const auto& n10 = n.column(1).x; const auto& n20 = n.column(2).x; const auto& n30 = n.column(3).x;
  const auto& n01 = n.column(0).y;  const auto& n11 = n.column(1).y; const auto& n21 = n.column(2).y; const auto& n31 = n.column(3).y;
  const auto& n02 = n.column(0).z;  const auto& n12 = n.column(1).z; const auto& n22 = n.column(2).z; const auto& n32 = n.column(3).z;
  const auto& n03 = n.column(0).w;  const auto& n13 = n.column(1).w; const auto& n23 = n.column(2).w; const auto& n33 = n.column(3).w;

  /**
            | mn00  mn10  mn20  mn30 |
    M x N = | mn01  mn11  mn21  mn31 |
            | mn02  mn12  mn22  mn32 |
            | mn03  mn13  mn23  mn33 |
  */
  return Matrix4<T>{
    m00 * n00 + m10 * n01 + m20 * n02 + m30 * n03, // mn00
    m01 * n00 + m11 * n01 + m21 * n02 + m31 * n03, // mn01
    m02 * n00 + m12 * n01 + m22 * n02 + m32 * n03, // mn02
    m03 * n00 + m13 * n01 + m23 * n02 + m33 * n03, // mn03

    m00 * n10 + m10 * n11 + m20 * n12 + m30 * n13, // mn10
    m01 * n10 + m11 * n11 + m21 * n12 + m31 * n13, // mn11
    m02 * n10 + m12 * n11 + m22 * n12 + m32 * n13, // mn12
    m03 * n10 + m13 * n11 + m23 * n12 + m33 * n13, // mn13

    m00 * n20 + m10 * n21 + m20 * n22 + m30 * n23, // mn20
    m01 * n20 + m11 * n21 + m21 * n22 + m31 * n23, // mn21
    m02 * n20 + m12 * n21 + m22 * n22 + m32 * n23, // mn22
    m03 * n20 + m13 * n21 + m23 * n22 + m33 * n23, // mn23

    m00 * n30 + m10 * n31 + m20 * n32 + m30 * n33, // mn30
    m01 * n30 + m11 * n31 + m21 * n32 + m31 * n33, // mn31
    m02 * n30 + m12 * n31 + m22 * n32 + m32 * n33, // mn32
    m03 * n30 + m13 * n31 + m23 * n32 + m33 * n33  // mn33
  };
}

template<typename T>
constexpr auto operator*(const Matrix4<T>& m, const Vector4<T>& v) noexcept -> Vector4<T> {
  /**
        | m00(x)   m10(x)   m20(x)   m30(x) |
    M = | m01(y)   m11(y)   m21(y)   m31(y) |
        | m02(z)   m12(z)   m22(z)   m32(z) |
        | m03(w)   m13(w)   m23(w)   m33(w) |
  */
  const auto& m00 = m.column(0).x;  const auto& m10 = m.column(1).x; const auto& m20 = m.column(2).x; const auto& m30 = m.column(3).x;
  const auto& m01 = m.column(0).y;  const auto& m11 = m.column(1).y; const auto& m21 = m.column(2).y; const auto& m31 = m.column(3).y;
  const auto& m02 = m.column(0).z;  const auto& m12 = m.column(1).z; const auto& m22 = m.column(2).z; const auto& m32 = m.column(3).z;
  const auto& m03 = m.column(0).w;  const auto& m13 = m.column(1).w; const auto& m23 = m.column(2).w; const auto& m33 = m.column(3).w;

  /**
        | vx |
    v = | vy |
        | vz |
        | vw |
  */

  /**
            | mvx  |
    M x v = | mvy  |
            | mvz  |
            | mvw  |
  */
  return Vector4<T>{
    m00 * v.x + m10 * v.y + m20 * v.z + m30 * v.w, // mvx
    m01 * v.x + m11 * v.y + m21 * v.z + m31 * v.w, // mvy
    m02 * v.x + m12 * v.y + m22 * v.z + m32 * v.w, // mvz
    m03 * v.x + m13 * v.y + m23 * v.z + m33 * v.w  // mvw
  };
}

} // namespace detail

using Mat4 = detail::Matrix4<float>;

} // namespace bonfire::math
