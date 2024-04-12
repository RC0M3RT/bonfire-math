#pragma once

#include <type_traits>
#include <cmath>

#include "vector3.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_floating_point_v<T>
struct Vector4 {
  T x, y, z, w;

  constexpr Vector4() noexcept : x{0}, y{0}, z{0}, w{0} {}
  constexpr explicit Vector4(T px, T py, T pz, T pw) noexcept : x{px}, y{py}, z{pz}, w{pw} {}
  constexpr explicit Vector4(T val) noexcept : x{val}, y{val}, z{val}, w{val} {}

  constexpr explicit Vector4(const Vector3<T>& v, const T pw) : x{v.x}, y{v.y}, z{v.z}, w{pw} {}

  constexpr Vector4(const Vector4<T>& other) noexcept : x{other.x}, y{other.y}, z{other.z}, w{other.w} {}
  constexpr Vector4(Vector4<T>&& other) noexcept : x{other.x}, y{other.y}, z{other.z}, w{other.w} {}

  constexpr auto operator==(const Vector4<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  constexpr auto elem(std::size_t elem_index) noexcept -> T& {
    return (&x)[elem_index];
  }

  constexpr auto elem(std::size_t elem_index) const noexcept -> const T& {
    return (&x)[elem_index];
  }

  constexpr auto operator=(const Vector4<T>& other) noexcept -> Vector4<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  constexpr auto operator=(Vector4<T>&& other) noexcept -> Vector4<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> Vector4<T>& {
    x *= val;
    y *= val;
    z *= val;
    w *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> Vector4<T>& {
    x /= val;
    y /= val;
    z /= val;
    w /= val;
    return *this;
  }

  constexpr auto operator+=(const Vector4<T>& other) noexcept -> Vector4<T>& {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  constexpr auto operator-=(const Vector4<T>& other) noexcept -> Vector4<T>& {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

};

template<typename T>
constexpr auto operator*(const Vector4<T>& vec, T val) noexcept -> Vector4<T> {
  return Vector4<T>{vec.x * val, vec.y * val, vec.z * val, vec.w * val};
}

template<typename T>
constexpr auto operator/(const Vector4<T>& vec, T val) noexcept -> Vector4<T> {
  return Vector4<T>{vec.x / val, vec.y / val, vec.z / val, vec.w / val};
}

template<typename T>
constexpr auto operator-(const Vector4<T>& vec) noexcept -> Vector4<T> {
  return Vector4<T>{-vec.x, -vec.y, -vec.z, -vec.w};
}

template<typename T>
constexpr auto operator+(const Vector4<T>& vec1, const Vector4<T>& vec2) noexcept -> Vector4<T> {
  return Vector4<T>{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w};
}

template<typename T>
constexpr auto operator-(const Vector4<T>& vec1, const Vector4<T>& vec2) noexcept -> Vector4<T> {
  return Vector4<T>{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::Vector4<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w)};
}

template<typename T>
constexpr auto normalize(const detail::Vector4<T>& vec) noexcept -> detail::Vector4<T> {
  return detail::Vector4<T>{vec / magnitude(vec)};
}

using Vec4 = detail::Vector4<float>;

} // namespace bonfire::math

#pragma clang diagnostic pop

