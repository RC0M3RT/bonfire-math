#include <chrono>
#include <cstdint>
#include <iostream>
#include <math/vector2.hpp>
#include <math/vector3.hpp>
#include <math/face.hpp>
#include <vector>

#include "core/renderer.hpp"

#include <internal_use_only/swr_config.hpp>

namespace bm = bonfire::math;

constexpr static auto WIDTH = 1280;
constexpr static auto HEIGHT = 720;

int main() {
  swr::Renderer renderer{WIDTH, HEIGHT};

  if (const auto res = renderer.initialize(); !res) {
    return -1;
  }

  std::string model_file = std::string(swr::CONTENT_BASE_PATH) + "/f117.obj";
  std::string texture_file = std::string(swr::CONTENT_BASE_PATH) + "/f117.png";

  swr::Entity e{};
  e.drawable = swr::load_model(model_file, texture_file);
  e.transform.position.z = 5.0f;
  e.transform.scale = bm::Vec3{1.0f, 1.0f, 1.0f};

  std::cout << "is: " << e.drawable.indices.size() << ", vs: " << e.drawable.vertices.size() << std::endl;

  e.update_transform = [](swr::TransformComponent& tr) {
    tr.rotation.x += 0.001f;
    // tr.rotation.y += 0.001f;
    // tr.rotation.z += 0.001f;
  };

  renderer.add_entity(std::move(e));

  renderer.render_forever();

  return 0;
}
