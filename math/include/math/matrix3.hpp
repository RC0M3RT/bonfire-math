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

  constexpr auto operator[](std::size_t column) noexcept -> Vector3<T>& { 
    return mat_[column];
  }

  constexpr auto operator[](std::size_t column) const noexcept -> const Vector3<T>& { 
    return mat_[column];
  }

private:
  Vector3<T> mat_[3];
};

template<typename T>
constexpr auto operator+(const Matrix3<T>& m1, const Matrix3<T>& m2) noexcept -> Matrix3<T> {
  return Matrix3<T>{m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2]};
}

template<typename T>
constexpr auto operator-(const Matrix3<T>& m1, const Matrix3<T>& m2) noexcept -> Matrix3<T> {
  return Matrix3<T>{m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2]};
}

} // namespace detail



using Mat3 = detail::Matrix3<float>;

}	// namespace bonfire::math

