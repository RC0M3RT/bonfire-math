#pragma once

#include <cstdint>
#include <future>
#include <math/vector2.hpp>
#include <math/vector3.hpp>
#include <vector>

#include "pods.hpp"

namespace swr {

using ColorBuffer = std::vector<std::uint32_t>;
using ZBuffer = std::vector<float>;

class Canvas {
 public:
  explicit Canvas(const int width, const int height) : width_(width), height_(height), color_buffer_(width * height), z_buffer_(width * height) {}

  [[nodiscard]] auto get_color_buffer() const -> const ColorBuffer& { return color_buffer_; }

  [[nodiscard]] auto get_width() const noexcept -> int { return width_; }

  [[nodiscard]] auto get_height() const noexcept -> int { return height_; }

  void clear_color(const std::uint32_t color) {
    for (std::size_t y = 0; y < height_; y++) {
      for (std::size_t x = 0; x < width_; x++) {
        color_buffer_[(width_ * y) + x] = color;
        z_buffer_[(width_ * y) + x] = 1.0f;
      }
    }
  }

  void draw_grid(const std::uint32_t grid_size) {
    for (std::size_t y = 0; y < height_; y++) {
      for (std::size_t x = 0; x < width_; x++) {
        if (x % grid_size == 0 || y % grid_size == 0) {
          color_buffer_[(width_ * y) + x] = 0xFF333333;
        }
      }
    }
  }

  template <typename T, typename V>
  constexpr void draw_rectangle(const T posx, const T posy, const V width, const V height, const std::uint32_t color) {
    draw_rectangle(static_cast<int>(posx), static_cast<int>(posy), static_cast<int>(width), static_cast<int>(height),
                   color);
  }

  void draw_rectangle(const int posx, const int posy, const int width, const int height, const std::uint32_t color) {
    for (std::size_t y = posy; y < posy + height; y++) {
      for (std::size_t x = posx; x < posx + width; x++) {
        color_buffer_[(width_ * y) + x] = color;
      }
    }
  }

  void draw_pixel(const int posx, const int posy, const std::uint32_t color) { color_buffer_[width_ * posy + posx] = color; }

  void draw_line(const int x0, const int y0, const int x1, const int y1, const std::uint32_t color) {
    // DDA line drawing algo
    const auto delta_x = x1 - x0;
    const auto delta_y = y1 - y0;

    const auto side_len = std::abs(delta_x) >= std::abs(delta_y) ? std::abs(delta_x) : std::abs(delta_y);

    // find how much we should increment in both x and y each step
    const float x_inc = static_cast<float>(delta_x) / static_cast<float>(side_len);
    const float y_inc = static_cast<float>(delta_y) / static_cast<float>(side_len);

    auto current_x = static_cast<float>(x0);
    auto current_y = static_cast<float>(y0);

    for (int i = 0; i <= side_len; i++) {
      draw_pixel(static_cast<int>(std::round(current_x)), static_cast<int>(std::round(current_y)), color);
      current_x += x_inc;
      current_y += y_inc;
    }
  }

  template <typename T>
  constexpr void draw_triangle(T x0, T y0, T x1, T y1, T x2, T y2, const std::uint32_t color) {
    draw_triangle(static_cast<int>(x0), static_cast<int>(y0), static_cast<int>(x1), static_cast<int>(y1),
                  static_cast<int>(x2), static_cast<int>(y2), color);
  }

  void draw_triangle(const int x0, const int y0, const int x1, const int y1, const int x2,
                     const int y2, const std::uint32_t color) {
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
  }

  template <typename T>
  constexpr void draw_filled_triangle(T x0, T y0, T x1, T y1, T x2, T y2, const std::uint32_t color) {
    draw_filled_triangle(static_cast<int>(x0), static_cast<int>(y0), static_cast<int>(x1), static_cast<int>(y1),
                         static_cast<int>(x2), static_cast<int>(y2), color);
  }

  void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2,
                            const std::uint32_t color) {
    // apply flat bottom, flat top technique
    // sort the vertices by y component ascending y0 < y1 < y2
    if (y0 > y1) {
      std::swap(y0, y1);
      std::swap(x0, x1);
    }
    if (y1 > y2) {
      std::swap(y1, y2);
      std::swap(x1, x2);
    }
    if (y0 > y1) {
      std::swap(y0, y1);
      std::swap(x0, x1);
    }

    // prevent divide by zero
    if (y1 == y2) {
      // if we dont have a bottom part of the triangle, draw from bottom to top
      draw_flat_bottom_triangle(x0, y0, x1, y1, x2, y2, color);
      return;
    }

    // prevent divide by zero
    if (y0 == y1) {
      // if we dont have the top part of the triangle, draw from top to bottom
      draw_flat_top_triangle(x0, y0, x1, y1, x2, y2, color);
      return;
    }

    // find triangle mid point
    const auto mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;
    const auto my = y1;

    // draw
    draw_flat_bottom_triangle(x0, y0, x1, y1, mx, my, color);
    draw_flat_top_triangle(x1, y1, mx, my, x2, y2, color);
  }

  // triangle midpoint, my = y1,  mx - x0 / x2 - x0 = y1 - y0 / y2 - y0
  // mx =  (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;  => triangle similarity

  void draw_textured_triangle(Vertex2 v0, Vertex2 v1, Vertex2 v2, const Texture& texture) {
    // We need to sort the vertices by y-coordinate ascending (y0 < y1 < y2)
    if (v0.y > v1.y) {
      std::swap(v0, v1);
    }
    if (v1.y > v2.y) {
      std::swap(v1, v2);
    }
    if (v0.y > v1.y) {
      std::swap(v0, v1);
    }

    // Render the upper part of the triangle (flat-bottom)

    float inv_slope_1 = 0;
    float inv_slope_2 = 0;

    if (v1.y - v0.y != 0) {
      inv_slope_1 = static_cast<float>((v1.x - v0.x)) / static_cast<float>(abs(v1.y - v0.y));
    }
    if (v2.y - v0.y != 0) {
      inv_slope_2 = static_cast<float>((v2.x - v0.x)) / static_cast<float>(abs(v2.y - v0.y));
    }

    if (v1.y - v0.y != 0) {
      for (int y = v0.y; y <= v1.y; y++) {
        int x_start = static_cast<int>(static_cast<float>(v1.x) + static_cast<float>((y - v1.y)) * inv_slope_1);
        int x_end = static_cast<int>(static_cast<float>(v0.x) + static_cast<float>((y - v0.y)) * inv_slope_2);

        if (x_end < x_start) {
          std::swap(x_start, x_end);  // swap if x_start is to the right of x_end
        }

        for (int x = x_start; x < x_end; x++) {
          // Draw our pixel with the color that comes from the texture
          Vertex2 vp{};
          vp.x = x;
          vp.y = y;

          draw_texel(v0, v1, v2, vp, texture);
        }
      }
    }

    // Render the bottom part of the triangle (flat-top)
    inv_slope_1 = 0;
    inv_slope_2 = 0;

    if (v2.y - v1.y != 0) {
      inv_slope_1 = static_cast<float>((v2.x - v1.x)) / static_cast<float>(abs(v2.y - v1.y));
    }
    if (v2.y - v0.y != 0) {
      inv_slope_2 = static_cast<float>((v2.x - v0.x)) / static_cast<float>(abs(v2.y - v0.y));
    }

    if (v2.y - v1.y != 0) {
      for (int y = v1.y; y <= v2.y; y++) {
        int x_start = static_cast<int>(static_cast<float>(v1.x) + static_cast<float>((y - v1.y)) * inv_slope_1);
        int x_end = static_cast<int>(static_cast<float>(v0.x) + static_cast<float>((y - v0.y)) * inv_slope_2);

        if (x_end < x_start) {
          std::swap(x_start, x_end);  // swap if x_start is to the right of x_end
        }

        for (int x = x_start; x < x_end; x++) {
          // Draw our pixel with the color that comes from the texture
          Vertex2 vp{};
          vp.x = x;
          vp.y = y;

          draw_texel(v0, v1, v2, vp, texture);
        }
      }
    }
  }

 private:
  void draw_flat_bottom_triangle(const int x0, const int y0, const int x1, const int y1, const int mx,
                                 const int my, const std::uint32_t color) {
    // find the 2 inverted slopes
    const float inv_slope0 = static_cast<float>((x1 - x0)) / static_cast<float>((y1 - y0));
    const float inv_slope1 = static_cast<float>((mx - x0)) / static_cast<float>((my - y0));

    // start the x_start and x_end from the top vertex
    auto x_start = static_cast<float>(x0);
    auto x_end = static_cast<float>(x0);

    for (int y = y0; y <= my; y++) {
      draw_line(static_cast<int>(x_start), y, static_cast<int>(x_end), y, color);

      x_start += inv_slope0;
      x_end += inv_slope1;
    }
  }

  void draw_flat_top_triangle(const int x1, const int y1, const int mx, const int my, const int x2,
                              const int y2, const std::uint32_t color) {
    // find the 2 inverted slopes
    const float inv_slope0 = static_cast<float>((x2 - x1)) / static_cast<float>((y2 - y1));
    const float inv_slope1 = static_cast<float>((x2 - mx)) / static_cast<float>((y2 - my));

    // start the x_start and x_end from the bottom vertex
    auto x_start = static_cast<float>(x2);
    auto x_end = static_cast<float>(x2);

    for (int y = y2; y >= my; y--) {
      draw_line(static_cast<int>(x_start), y, static_cast<int>(x_end), y, color);

      x_start -= inv_slope0;
      x_end -= inv_slope1;
    }
  }

  void draw_texel(const Vertex2& a, const Vertex2& b, const Vertex2& c, const Vertex2& p, const Texture& texture) {
    const auto weights = barycentric_weights(a, b, c, p);

    const float alpha = weights.x;
    const float beta = weights.y;
    const float gamma = weights.z;

    // Perform the interpolation of all U and V values using barycentric weights
    const float interpolated_u = (a.u) * alpha + (b.u) * beta + (c.u) * gamma;
    const float interpolated_v = (a.v) * alpha + (b.v) * beta + (c.v) * gamma;

    // Map the UV coordinate to the full texture width and height
    const int tex_x = static_cast<int>(abs(interpolated_u * static_cast<float>(texture.width))) % static_cast<int>(texture.width);
    const int tex_y = static_cast<int>(abs(interpolated_v * static_cast<float>(texture.height))) % static_cast<int>(texture.height);

    const auto idx = ((texture.width * tex_y) + tex_x);

    draw_pixel(p.x, p.y, texture.texels[idx]);
  }

  static auto barycentric_weights(const Vertex2& a, const Vertex2& b, const Vertex2& c, const Vertex2& p)
      -> bonfire::math::float3 {
    // Find the vectors between the vertices ABC and point p
    const auto ac = c - a;
    const auto ab = b - a;
    const auto ap = p - a;
    const auto pc = c - p;
    const auto pb = b - p;

    // Compute the area of the full parallegram/triangle ABC using 2D cross product
    const auto area_parallelogram_abc = static_cast<float>((ac.x * ab.y - ac.y * ab.x));  // || AC x AB ||

    // Alpha is the area of the small parallelogram/triangle PBC divided by the area of the full parallelogram/triangle ABC
    const float alpha = static_cast<float>((pc.x * pb.y - pc.y * pb.x)) / area_parallelogram_abc;

    // Beta is the area of the small parallelogram/triangle APC divided by the area of the full parallelogram/triangle ABC
    const float beta = static_cast<float>((ac.x * ap.y - ac.y * ap.x)) / area_parallelogram_abc;

    // Weight gamma is easily found since barycentric coordinates always add up to 1.0
    const float gamma = std::abs(1.0f - alpha - beta);

    return bonfire::math::float3{std::abs(alpha), std::abs(beta), gamma};
  }

private:
  int width_;
  int height_;
  ColorBuffer color_buffer_;
  ZBuffer z_buffer_;
};

}  // namespace swr
