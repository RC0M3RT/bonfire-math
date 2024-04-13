#pragma once

#include <cstdint>
#include <vector>

namespace swr {

using ColorBuffer = std::vector<std::uint32_t>;

class Canvas {
 public:
  explicit Canvas(const int width, const int height) : width_(width), height_(height), color_buffer_(width * height) {}

  [[nodiscard]] auto get_color_buffer() const -> const ColorBuffer& { return color_buffer_; }

  [[nodiscard]] auto get_width() const noexcept -> int { return width_; }

  [[nodiscard]] auto get_height() const noexcept -> int { return height_; }

  void clear_color(const std::uint32_t color) {
    for (std::size_t y = 0; y < height_; y++) {
      for (std::size_t x = 0; x < width_; x++) {
        color_buffer_[(width_ * y) + x] = color;
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
    const int delta_y = y1 - y0;

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

private:
  int width_;
  int height_;
  ColorBuffer color_buffer_;
};

}  // namespace swr
