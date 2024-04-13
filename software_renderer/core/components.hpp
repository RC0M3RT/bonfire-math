#pragma once

#include <vector>

#include <math/vector3.hpp>

namespace swr {

struct TransformComponent {
  bonfire::math::Vec3 position{0.f};
  bonfire::math::Vec3 rotation{};
  bonfire::math::Vec3 scale{1.0f};
};

struct DrawableComponent {
  std::vector<bonfire::math::Vec3> vertices{};
  std::vector<std::uint32_t> indices{};
};

} // namespace swr
