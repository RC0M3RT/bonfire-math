#pragma once

#include <vector>
#include <functional>

#include "components.hpp"

namespace swr {

struct Entity {
  DrawableComponent drawable{};
  TransformComponent transform{};

  std::function<void(TransformComponent& tc)> update_transform{}; 
};

}	// namespace swr
