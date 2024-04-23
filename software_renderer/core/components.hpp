#pragma once

#include <vector>

#include <math/vector3.hpp>

namespace swr {

struct TransformComponent {
  bonfire::math::Vec3 position{0.f};
  bonfire::math::Vec3 rotation{};
  bonfire::math::Vec3 scale{1.0f};
};

struct Vertex {
  bonfire::math::Vec3 pos;
  bonfire::math::Vec2 uv;

  constexpr auto operator==(const Vertex& other) const -> bool {
    return pos == other.pos;
  }
};

struct DrawableComponent {
  std::vector<Vertex> vertices{};
  std::vector<std::uint32_t> indices{};
  Texture texture{};
};

} // namespace swr
