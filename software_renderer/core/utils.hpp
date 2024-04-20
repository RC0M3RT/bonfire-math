#pragma once

#include <cstdint>

namespace swr {

static std::uint32_t light_apply_intensity(const std::uint32_t original_color, float percentage_factor) {
  if (percentage_factor <= 0.0f) {
    percentage_factor = 0.1f;
  }

  if (percentage_factor >= 1.0f) {
    percentage_factor = .9f;
  }

  const std::uint32_t a = (original_color & 0xFF000000);
  const auto r = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x00FF0000)) * percentage_factor);
  const auto g = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x0000FF00)) * percentage_factor);
  const auto b = static_cast<std::uint32_t>(static_cast<float>((original_color & 0x000000FF)) * percentage_factor);

  const std::uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
  return new_color;
}

} // namespace swr