#pragma once

#include <type_traits>
#include <cmath>

#include "vector3.hpp"

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_arithmetic_v<T>
struct vector4 {
  T x, y, z, w;

  constexpr vector4() noexcept : x{0}, y{0}, z{0}, w{0} {}
  constexpr explicit vector4(T px, T py, T pz, T pw) noexcept : x{px}, y{py}, z{pz}, w{pw} {}
  constexpr explicit vector4(T val) noexcept : x{val}, y{val}, z{val}, w{val} {}

  constexpr explicit vector4(const vector3<T>& v, const T pw) : x{v.x}, y{v.y}, z{v.z}, w{pw} {}

  constexpr vector4(const vector4<T>& other) noexcept : x{other.x}, y{other.y}, z{other.z}, w{other.w} {}
  constexpr vector4(vector4<T>&& other) noexcept : x{other.x}, y{other.y}, z{other.z}, w{other.w} {}

  constexpr auto to_vec3() const noexcept -> vector3<T> {
    return vector3<T> {
      x, y, z
    };
  }

  constexpr auto operator==(const vector4<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y && z == other.z && w == other.w;
  }

  constexpr auto operator=(const vector4<T>& other) noexcept -> vector4<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  constexpr auto operator=(vector4<T>&& other) noexcept -> vector4<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> vector4<T>& {
    x *= val;
    y *= val;
    z *= val;
    w *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> vector4<T>& {
    x /= val;
    y /= val;
    z /= val;
    w /= val;
    return *this;
  }

  constexpr auto operator+=(const vector4<T>& other) noexcept -> vector4<T>& {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
  }

  constexpr auto operator-=(const vector4<T>& other) noexcept -> vector4<T>& {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
  }

};

template<typename T>
constexpr auto operator*(const vector4<T>& vec, T val) noexcept -> vector4<T> {
  return vector4<T>{vec.x * val, vec.y * val, vec.z * val, vec.w * val};
}

template<typename T>
constexpr auto operator/(const vector4<T>& vec, T val) noexcept -> vector4<T> {
  return vector4<T>{vec.x / val, vec.y / val, vec.z / val, vec.w / val};
}

template<typename T>
constexpr auto operator-(const vector4<T>& vec) noexcept -> vector4<T> {
  return vector4<T>{-vec.x, -vec.y, -vec.z, -vec.w};
}

template<typename T>
constexpr auto operator+(const vector4<T>& vec1, const vector4<T>& vec2) noexcept -> vector4<T> {
  return vector4<T>{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w};
}

template<typename T>
constexpr auto operator-(const vector4<T>& vec1, const vector4<T>& vec2) noexcept -> vector4<T> {
  return vector4<T>{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::vector4<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w)};
}

template<typename T>
constexpr auto normalize(const detail::vector4<T>& vec) noexcept -> detail::vector4<T> {
  return detail::vector4<T>{vec / magnitude(vec)};
}

using float4 = detail::vector4<float>;
using int4 = detail::vector4<int>;

} // namespace bonfire::math

