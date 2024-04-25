#pragma once

#include <math/vector3.hpp>

namespace swr {

struct Vertex2 {
  int x, y;
  float u, v;

  explicit Vertex2(const bonfire::math::float2& pos, const bonfire::math::float2& uv) noexcept
      : x{static_cast<int>(pos.x)}, y{static_cast<int>(pos.y)}, u{uv.x}, v{uv.y} {}
  explicit Vertex2(const int px, const int py) noexcept : x{px}, y{py}, u{}, v{} {}
  Vertex2() noexcept = default;
};

inline auto operator+(const Vertex2& vec1, const Vertex2& vec2) noexcept -> Vertex2 { return Vertex2{vec1.x + vec2.x, vec1.y + vec2.y}; }

inline auto operator-(const Vertex2& vec1, const Vertex2& vec2) noexcept -> Vertex2 { return Vertex2{vec1.x - vec2.x, vec1.y - vec2.y}; }

struct Light {
  bonfire::math::float3 direction;
};

struct Texture {
  std::uint32_t width{};
  std::uint32_t height{};

  std::vector<std::uint32_t> texels{};
};

} // namespace swr

