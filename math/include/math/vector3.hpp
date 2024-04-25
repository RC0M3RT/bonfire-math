#pragma once

#include <type_traits>
#include <cmath>

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_arithmetic_v<T>
struct vector3 {
  T x, y, z;

  constexpr vector3() noexcept : x{0}, y{0}, z{0} {}
  constexpr explicit vector3(T px, T py, T pz) noexcept : x{px}, y{py}, z{pz} {}
  constexpr explicit vector3(T val) noexcept : x{val}, y{val}, z{val} {}

  constexpr vector3(const vector3<T>& other) noexcept : x{other.x}, y{other.y}, z{other.z} {}
  constexpr vector3(vector3<T>&& other) noexcept : x{other.x}, y{other.y}, z{other.z} {}

  constexpr auto operator==(const vector3<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y && z == other.z;
  }

  constexpr auto operator=(const vector3<T>& other) noexcept -> vector3<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  constexpr auto operator=(vector3<T>&& other) noexcept -> vector3<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> vector3<T>& {
    x *= val;
    y *= val;
    z *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> vector3<T>& {
    x /= val;
    y /= val;
    z /= val;
    return *this;
  }

  constexpr auto operator+=(const vector3<T>& other) noexcept -> vector3<T>& {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  constexpr auto operator-=(const vector3<T>& other) noexcept -> vector3<T>& {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

};

template<typename T>
constexpr auto operator*(const vector3<T>& vec, T val) noexcept -> vector3<T> {
  return vector3<T>{vec.x * val, vec.y * val, vec.z * val};
}

template<typename T>
constexpr auto operator/(const vector3<T>& vec, T val) noexcept -> vector3<T> {
  return vector3<T>{vec.x / val, vec.y / val, vec.z / val};
}

template<typename T>
constexpr auto operator-(const vector3<T>& vec) noexcept -> vector3<T> {
  return vector3<T>{-vec.x, -vec.y, -vec.z};
}

template<typename T>
constexpr auto operator+(const vector3<T>& vec1, const vector3<T>& vec2) noexcept -> vector3<T> {
  return vector3<T>{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

template<typename T>
constexpr auto operator-(const vector3<T>& vec1, const vector3<T>& vec2) noexcept -> vector3<T> {
  return vector3<T>{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::vector3<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)};
}

template<typename T>
constexpr auto normalize(const detail::vector3<T>& vec) noexcept -> detail::vector3<T> {
  return detail::vector3<T>{vec / magnitude(vec)};
}

template<typename T>
constexpr auto rotate_x(const detail::vector3<T>& vec, const T angle) noexcept -> detail::vector3<T> {
  return detail::vector3<T>{
    vec.x, // x
    vec.y * std::cos(angle) - vec.z * std::sin(angle), // y
    vec.y * std::sin(angle) + vec.z * std::cos(angle) // z
  };
}

template<typename T>
constexpr auto rotate_y(const detail::vector3<T>& vec, const T angle) noexcept -> detail::vector3<T> {
  return detail::vector3<T>{
    vec.x * std::cos(angle) - vec.z * std::sin(angle), // x
    vec.y, // y
    vec.x * std::sin(angle) + vec.z * std::cos(angle) // z
  };
}

template<typename T>
constexpr auto rotate_z(const detail::vector3<T>& vec, const T angle) noexcept -> detail::vector3<T> {
  return detail::vector3<T>{
    vec.x * std::cos(angle) - vec.y * std::sin(angle), // x
    vec.x * std::sin(angle) + vec.y * std::cos(angle), // y
    vec.z // z
  };
}

template<typename T>
constexpr auto cross_product(const detail::vector3<T>& vec1, const detail::vector3<T>& vec2) noexcept -> detail::vector3<T> {
  return detail::vector3<T>{
    vec1.y * vec2.z - vec1.z * vec2.y,
    vec1.z * vec2.x - vec1.x * vec2.z,
    vec1.x * vec2.y - vec1.y * vec2.x
  };
}

template<typename T>
constexpr auto dot_product(const detail::vector3<T>& vec1, const detail::vector3<T>& vec2) noexcept -> T {
  return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

using float3 = detail::vector3<float>;
using int3 = detail::vector3<int>;

} // namespace bonfire::math

