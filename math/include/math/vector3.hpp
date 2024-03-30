#pragma once

#include <type_traits>

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_floating_point_v<T>
struct Vector3 {
  T x, y, z;

  constexpr Vector3() noexcept : x{0}, y{0}, z{0} {}
  constexpr explicit Vector3(T px, T py, T pz) noexcept : x{px}, y{py}, z{pz} {}
  constexpr explicit Vector3(T val) noexcept : x{val}, y{val}, z{val} {}

  constexpr Vector3(const Vector3<T>& other) noexcept : x{other.x}, y{other.y}, z{other.z} {}
  constexpr Vector3(Vector3<T>&& other) noexcept : x{other.x}, y{other.y}, z{other.z} {}

  constexpr auto operator==(const Vector3<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y && z == other.z;
  }

  constexpr auto operator[](std::size_t i) noexcept -> T& { 
    return (&x)[i];
  }

  constexpr auto operator[](std::size_t i) const noexcept -> const T& { 
    return (&x)[i];
  }

  constexpr auto operator=(const Vector3<T>& other) noexcept -> Vector3<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  constexpr auto operator=(Vector3<T>&& other) noexcept -> Vector3<T>& {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> Vector3<T>& {
    x *= val;
    y *= val;
    z *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> Vector3<T>& {
    x /= val;
    y /= val;
    z /= val;
    return *this;
  }

  constexpr auto operator+=(const Vector3<T>& other) noexcept -> Vector3<T>& {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }

  constexpr auto operator-=(const Vector3<T>& other) noexcept -> Vector3<T>& {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
  }

};

template<typename T>
constexpr auto operator*(const Vector3<T>& vec, T val) noexcept -> Vector3<T> {
  return Vector3<T>{vec.x * val, vec.y * val, vec.z * val};
}

template<typename T>
constexpr auto operator/(const Vector3<T>& vec, T val) noexcept -> Vector3<T> {
  return Vector3<T>{vec.x / val, vec.y / val, vec.z / val};
}

template<typename T>
constexpr auto operator-(const Vector3<T>& vec) noexcept -> Vector3<T> {
  return Vector3<T>{-vec.x, -vec.y, -vec.z};
}

template<typename T>
constexpr auto operator+(const Vector3<T>& vec1, const Vector3<T>& vec2) noexcept -> Vector3<T> {
  return Vector3<T>{vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z};
}

template<typename T>
constexpr auto operator-(const Vector3<T>& vec1, const Vector3<T>& vec2) noexcept -> Vector3<T> {
  return Vector3<T>{vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::Vector3<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z)};
}

template<typename T>
constexpr auto normalize(const detail::Vector3<T>& vec) noexcept -> detail::Vector3<T> {
  return detail::Vector3<T>{vec / magnitude(vec)};
}

using Vec3 = detail::Vector3<float>;

}	// namespace bonfire::math
