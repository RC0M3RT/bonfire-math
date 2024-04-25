#pragma once

#include <cstdint>
#include <functional>

#include "pods.hpp"

#include "stb_image.h"
#include <tiny_obj_loader.h>

#include <internal_use_only/swr_config.hpp>

namespace swr {

static std::uint32_t light_apply_intensity(const std::uint32_t original_color, float percentage_factor) {
  const std::uint32_t a = (original_color & 0xFF000000);
  const auto r = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x00FF0000)) * percentage_factor);
  const auto g = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x0000FF00)) * percentage_factor);
  const auto b = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x000000FF)) * percentage_factor);

  const std::uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
  return new_color;
}

static Texture load_texture(const std::string& filename) {
  int width, height;
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, nullptr, 4);

  if (!data) {
    std::cerr << stbi_failure_reason() << "\n";
    return {};
  }

  Texture t{};
  t.width = width;
  t.height = height;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      const unsigned char* pixel_offset = data + (width * j + i) * 4;
      const unsigned char r = pixel_offset[0];
      const unsigned char g = pixel_offset[1];
      const unsigned char b = pixel_offset[2];
      const unsigned char a = pixel_offset[3];

      const std::uint32_t new_color = a << 24 | r << 16 | g << 8 | b;
      t.texels.push_back(new_color);
    }
  }

  stbi_image_free(data);
  return t;
}

template <>
struct std::hash<swr::Vertex> {
  std::size_t operator()(const swr::Vertex& k) const noexcept {
    using std::hash;
    using std::size_t;

    return ((hash<float>()(k.pos.x) ^ (hash<float>()(k.pos.y) << 1)) >> 1) ^ (hash<float>()(k.pos.z) << 1);
  }
};

static DrawableComponent load_model(const std::string& filename, const std::optional<std::string>& texture_filename = std::nullopt) {
  namespace bm = bonfire::math;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;

  std::string warn;
  std::string err;

  bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str());

  if (!warn.empty()) {
    std::cerr << warn << std::endl;
  }

  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  if (!ret) {
    return {};
  }

  DrawableComponent dc{};

  if (texture_filename.has_value()) {
    dc.texture = load_texture(*texture_filename);
  }

  std::unordered_map<Vertex, uint32_t> unique_vertices{};

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      Vertex vertex;

      vertex.pos = bm::float3{
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };

      vertex.uv = bm::float2{
        attrib.texcoords[2 * index.texcoord_index + 0],
        attrib.texcoords[2 * index.texcoord_index + 1],
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

} // namespace swr