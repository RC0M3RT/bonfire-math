#include <chrono>
#include <cstdint>
#include <iostream>
#include <math/vector2.hpp>
#include <math/vector3.hpp>
#include <math/face.hpp>
#include <vector>

#include "core/renderer.hpp"

#include <internal_use_only/swr_config.hpp>

#include <tiny_obj_loader.h>

namespace bm = bonfire::math;

constexpr static auto WIDTH = 1280;
constexpr static auto HEIGHT = 720;

template <>
struct std::hash<bm::Vec3> {
  std::size_t operator()(const bm::Vec3& k) const noexcept {
    using std::hash;
    using std::size_t;

    return ((hash<float>()(k.x) ^ (hash<float>()(k.y) << 1)) >> 1) ^ (hash<float>()(k.z) << 1);
  }
};

swr::DrawableComponent load_model() {
  std::string input_file = std::string(swr::CONTENT_BASE_PATH) + "/f22.obj";
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, input_file.c_str());

  if (!warn.empty()) {
    std::cerr << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  if (!ret) {
    return {};
  }

  swr::DrawableComponent dc{};

  std::unordered_map<bm::Vec3, uint32_t> unique_vertices{};

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      bm::Vec3 vertex{};

      vertex = bm::Vec3{
        attrib.vertices[3 * index.vertex_index + 0], 
        attrib.vertices[3 * index.vertex_index + 1], 
        attrib.vertices[3 * index.vertex_index + 2]
      };

      if (!unique_vertices.contains(vertex)) {
        unique_vertices[vertex] = static_cast<uint32_t>(dc.vertices.size());
        dc.vertices.push_back(vertex);
      }

      dc.indices.push_back(unique_vertices[vertex]);
    }
  }

  return dc;
}

int main() {
  swr::Renderer renderer{WIDTH, HEIGHT};

  if (const auto res = renderer.initialize(); !res) {
    return -1;
  }

  std::vector<bm::Vec3> vertices;

  std::vector<bm::Face> faces;

  swr::Entity e{};
  e.drawable = load_model();
  e.transform.position.z = -5;

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
