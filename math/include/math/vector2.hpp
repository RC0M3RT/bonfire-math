#pragma once

#include <type_traits>

namespace bonfire::math {

namespace detail {

template<typename T> requires std::is_arithmetic_v<T>
struct vector2 {
  T x, y;

  constexpr vector2() noexcept : x{0}, y{0} {}
  constexpr explicit vector2(T px, T py) noexcept : x{px}, y{py} {}
  constexpr explicit vector2(T val) noexcept : x{val}, y{val} {}

  constexpr vector2(const vector2<T>& other) noexcept : x{other.x}, y{other.y} {}
  constexpr vector2(vector2<T>&& other) noexcept : x{other.x}, y{other.y} {}

  constexpr auto operator==(const vector2<T>& other) const noexcept -> bool {
    return x == other.x && y == other.y;
  }

  constexpr auto operator=(const vector2<T>& other) noexcept -> vector2<T>& {
    x = other.x;
    y = other.y;
    return *this;
  }

  constexpr auto operator=(vector2<T>&& other) noexcept -> vector2<T>& {
    x = other.x;
    y = other.y;
    return *this;
  }

  constexpr auto operator*=(T val) noexcept -> vector2<T>& {
    x *= val;
    y *= val;
    return *this;
  }

  constexpr auto operator/=(T val) noexcept -> vector2<T>& {
    x /= val;
    y /= val;
    return *this;
  }

  constexpr auto operator+=(const vector2<T>& other) noexcept -> vector2<T>& {
    x += other.x;
    y += other.y;
    return *this;
  }

  constexpr auto operator-=(const vector2<T>& other) noexcept -> vector2<T>& {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  constexpr auto magnitude() const noexcept -> T {
    return T{std::sqrt(x * x + y * y)};
  }
};

template<typename T>
constexpr auto operator*(const vector2<T>& vec, T val) noexcept -> vector2<T> {
  return vector2<T>{vec.x * val, vec.y * val};
}

template<typename T>
constexpr auto operator/(const vector2<T>& vec, T val) noexcept -> vector2<T> {
  return vector2<T>{vec.x / val, vec.y / val};
}

template<typename T>
constexpr auto operator-(const vector2<T>& vec) noexcept -> vector2<T> {
  return vector2<T>{-vec.x, -vec.y};
}

template<typename T>
constexpr auto operator+(const vector2<T>& vec1, const vector2<T>& vec2) noexcept -> vector2<T> {
  return vector2<T>{vec1.x + vec2.x, vec1.y + vec2.y};
}

template<typename T>
constexpr auto operator-(const vector2<T>& vec1, const vector2<T>& vec2) noexcept -> vector2<T> {
  return vector2<T>{vec1.x - vec2.x, vec1.y - vec2.y};
}

} // namespace detail

template<typename T>
constexpr auto magnitude(const detail::vector2<T>& vec) noexcept -> T {
  return T{std::sqrt(vec.x * vec.x + vec.y * vec.y)};
}

template<typename T>
constexpr auto normalize(const detail::vector2<T>& vec) noexcept -> detail::vector2<T> {
  return detail::vector2<T>{vec / magnitude(vec)};
}

template<typename T>
constexpr auto dot_product(const detail::vector2<T>& vec1, const detail::vector2<T>& vec2) noexcept -> T {
  return vec1.x * vec2.x + vec1.y * vec2.y;
}

using float2 = detail::vector2<float>;
using int2 = detail::vector2<int>;

} // namespace bonfire::math

