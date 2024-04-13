#pragma once

#include "vector3.hpp"

namespace bonfire::math {

namespace detail {

/**
 * Column-major order 3 dimentional matrix
 */
template<typename T> requires std::is_floating_point_v<T>
struct Matrix3 {
  /**
   * @brief Zero initialize matrix
   */
  constexpr Matrix3() noexcept : mat_{} {}

  /**
   * @brief Construct a matrix while initializing all members to given val
   */
  constexpr explicit Matrix3(T val) noexcept : mat_{Vector3<T>{val}, Vector3<T>{val}, Vector3<T>{val}} {}

  /**
   * @brief Per member initialize matrix
   */
  constexpr explicit Matrix3(T p0x, T p0y, T p0z, T p1x, T p1y, T p1z, T p2x, T p2y, T p2z) noexcept
      : mat_{Vector3<T>{p0x, p0y, p0z}, Vector3<T>{p1x, p1y, p1z}, Vector3<T>{p2x, p2y, p2z}} {}

  /**
   * @brief Construct a matrix from 3 vectors
   */
  constexpr explicit Matrix3(const Vector3<T>& p0, const Vector3<T>& p1, const Vector3<T>& p2) noexcept : mat_{p0, p1, p2} {}

  constexpr auto operator==(const Matrix3<T>& other) const noexcept -> bool { 
    return mat_[0] == other.mat_[0] && mat_[1] == other.mat_[1] && mat_[2] == other.mat_[2];
  }

  constexpr auto column(std::size_t column_index) noexcept -> Vector3<T>& { 
    return mat_[column_index];
  }

  constexpr auto column(std::size_t column_index) const noexcept -> const Vector3<T>& { 
    return mat_[column_index];
  }

private:
  Vector3<T> mat_[3];
};

template<typename T>
constexpr auto operator+(const Matrix3<T>& m, const Matrix3<T>& n) noexcept -> Matrix3<T> {
  return Matrix3<T>{m.column(0) + n.column(0), m.column(1) + n.column(1), m.column(2) + n.column(2)};
}

template<typename T>
constexpr auto operator-(const Matrix3<T>& m, const Matrix3<T>& n) noexcept -> Matrix3<T> {
  return Matrix3<T>{m.column(0) - n.column(0), m.column(1) - n.column(1), m.column(2) - n.column(2)};
}

template<typename T>
constexpr auto operator*(const Matrix3<T>& m, T val) noexcept -> Matrix3<T> {
  return Matrix3<T>{m.column(0) * val, m.column(1) * val, m.column(2) * val};
}

template<typename T>
constexpr auto operator/(const Matrix3<T>& m, T val) noexcept -> Matrix3<T> {
  return Matrix3<T>{m.column(0) / val, m.column(1) / val, m.column(2) / val};
}

template<typename T>
constexpr auto operator*(const Matrix3<T>& m, const Matrix3<T>& n) noexcept -> Matrix3<T> {
  /**
        | m00(x)   m10(x)   m20(x) |
    M = | m01(y)   m11(y)   m21(y) |
        | m02(z)   m12(z)   m22(z) |
  */
  const auto& m00 = m.column(0).x;  const auto& m10 = m.column(1).x; const auto& m20 = m.column(2).x;
  const auto& m01 = m.column(0).y;  const auto& m11 = m.column(1).y; const auto& m21 = m.column(2).y;
  const auto& m02 = m.column(0).z;  const auto& m12 = m.column(1).z; const auto& m22 = m.column(2).z;

  /**
        | n00(x)   n10(x)   n20(x) |
    N = | n01(y)   n11(y)   n21(y) |
        | n02(z)   n12(z)   n22(z) |
  */
  const auto& n00 = n.column(0).x;  const auto& n10 = n.column(1).x; const auto& n20 = n.column(2).x;
  const auto& n01 = n.column(0).y;  const auto& n11 = n.column(1).y; const auto& n21 = n.column(2).y;
  const auto& n02 = n.column(0).z;  const auto& n12 = n.column(1).z; const auto& n22 = n.column(2).z;

  /**
            | mn00  mn10  mn20  |
    M x N = | mn01  mn11  mn21  |
            | mn02  mn12  mn22  |
  */
  return Matrix3<T>{
    m00 * n00 + m10 * n01 + m20 * n02, // mn00
    m01 * n00 + m11 * n01 + m21 * n02, // mn01
    m02 * n00 + m12 * n01 + m22 * n02, // mn02
    m00 * n10 + m10 * n11 + m20 * n12, // mn10
    m01 * n10 + m11 * n11 + m21 * n12, // mn11
    m02 * n10 + m12 * n11 + m22 * n12, // mn12
    m00 * n20 + m10 * n21 + m20 * n22, // mn20
    m01 * n20 + m11 * n21 + m21 * n22, // mn21
    m02 * n20 + m12 * n21 + m22 * n22  // mn22
  };
}

template<typename T>
constexpr auto operator*(const Matrix3<T>& m, const Vector3<T>& v) noexcept -> Vector3<T> {
  /**
        | m00(x)   m10(x)   m20(x) |
    M = | m01(y)   m11(y)   m21(y) |
        | m02(z)   m12(z)   m22(z) |
  */
  const auto& m00 = m.column(0).x;  const auto& m10 = m.column(1).x; const auto& m20 = m.column(2).x;
  const auto& m01 = m.column(0).y;  const auto& m11 = m.column(1).y; const auto& m21 = m.column(2).y;
  const auto& m02 = m.column(0).z;  const auto& m12 = m.column(1).z; const auto& m22 = m.column(2).z;

  /**
        | vx |
    v = | vy |
        | vz |
  */

  /**
            | mvx  |
    M x v = | mvy  |
            | mvz  |
  */
  return Vector3<T>{
    m00 * v.x + m10 * v.y + m20 * v.z, // mvx
    m01 * v.x + m11 * v.y + m21 * v.z, // mvy
    m02 * v.x + m12 * v.y + m22 * v.z  // mvz
  };
}

} // namespace detail


using Mat3 = detail::Matrix3<float>;

} // namespace bonfire::math

