#pragma once

#include <type_traits>

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_floating_point_v<T>
struct Vector2 {
  T x, y;

  constexpr Vector2() noexcept : x{0}, y{0} {}
  constexpr explicit Vector2(T px, T py) noexcept : x{px}, y{py} {}
  constexpr explicit Vector2(T val) noexcept : x{val}, y{val} {}

  constexpr Vector2(const Vector2<T>& other) noexcept : x{other.x}, y{other.y} {}
  constexpr Vector2(Vector2<T>&& other) noexcept : x{other.x}, y{other.y} {}

  constexpr auto operator==(const Vector2<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y;
  }

  constexpr auto operator=(const Vector2<T>& other) noexcept -> Vector2<T>& {
    x = other.x;
    y = other.y;
    return *this;
  }

  constexpr auto operator=(Vector2<T>&& other) noexcept -> Vector2<T>& {
    x = other.x;
    y = other.y;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> Vector2<T>& {
    x *= val;
    y *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> Vector2<T>& {
    x /= val;
    y /= val;
    return *this;
  }

  constexpr auto operator+=(const Vector2<T>& other) noexcept -> Vector2<T>& {
    x += other.x;
    y += other.y;
    return *this;
  }

  constexpr auto operator-=(const Vector2<T>& other) noexcept -> Vector2<T>& {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  constexpr auto magnitude() const noexcept -> T {
    return T{std::sqrt(x * x + y * y)};
  }
};

template<typename T>
constexpr auto operator*(const Vector2<T>& vec, T val) noexcept -> Vector2<T> {
  return Vector2<T>{vec.x * val, vec.y * val};
}

template<typename T>
constexpr auto operator/(const Vector2<T>& vec, T val) noexcept -> Vector2<T> {
  return Vector2<T>{vec.x / val, vec.y / val};
}

template<typename T>
constexpr auto operator-(const Vector2<T>& vec) noexcept -> Vector2<T> {
  return Vector2<T>{-vec.x, -vec.y};
}

template<typename T>
constexpr auto operator+(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept -> Vector2<T> {
  return Vector2<T>{vec1.x + vec2.x, vec1.y + vec2.y};
}

template<typename T>
constexpr auto operator-(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept -> Vector2<T> {
  return Vector2<T>{vec1.x - vec2.x, vec1.y - vec2.y};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::Vector2<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y)};
}

template<typename T>
constexpr auto normalize(const detail::Vector2<T>& vec) noexcept -> detail::Vector2<T> {
  return detail::Vector2<T>{vec / magnitude(vec)};
}

template<typename T>
constexpr auto dot_product(const detail::Vector2<T>& vec1, const detail::Vector2<T>& vec2) noexcept -> T {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

using Vec2 = detail::Vector2<float>;

} // namespace bonfire::math

