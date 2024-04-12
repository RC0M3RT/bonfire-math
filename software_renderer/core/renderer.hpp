#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <math/vector2.hpp>

#include "canvas.hpp"
#include "context.hpp"
#include "entity.hpp"

namespace swr {

struct RenderOptions {
  bool enable_back_face_culling = true;
  bool render_wireframe = true;
  bool render_filled_triangle = false;
  bool render_vertex_points = false;
};

struct Triangle {
  bonfire::math::Vec2 points[3] = {};
  float avg_depth = 0.0f;
};

struct RenderData {
  std::vector<Triangle> triangles{};
};

class Renderer {
public:
  explicit Renderer(const int width, const int height) noexcept
    : canvas_{width, height}, context_{}, entities_{}, camera_pos_{0.0f}, options_{}, is_running_{false} {}

  [[nodiscard]] auto initialize() -> bool {
    auto ctx = Context::create_context(canvas_.get_width(), canvas_.get_height());
    if (ctx.has_value()) {
      context_ = std::move(*ctx);
      return true;
    }

    return false;
  }

  void stop() {
    is_running_ = false;
  }

  void add_entity(Entity&& entity) {
    RenderData rd {};
    rd.triangles.reserve(entity.drawable.indices.size() / 3);
    render_datas_.push_back(std::move(rd));
    entities_.emplace_back(std::move(entity));
  }

  void render_forever() {
    if (!context_.window || !context_.renderer || !context_.color_buffer_texture) {
      std::cerr << "Make sure to call after successful initialize" << std::endl;
      return;
    }

    is_running_ = true;

    auto current_time = std::chrono::high_resolution_clock::now();

    while (is_running_) [[likely]] {
      process_input();

      auto new_time = std::chrono::high_resolution_clock::now();
      const auto delta_time = std::chrono::duration<float, std::chrono::seconds::period>(new_time - current_time).count();

      current_time = new_time;

      update(delta_time);
      render();
    }

    context_.cleanup();
  }

private:
  void process_input() {
    SDL_Event ev;
    SDL_PollEvent(&ev);

    switch (ev.type) {
      case SDL_QUIT: {
        std::cout << "SDL_QUIT" << std::endl;
        is_running_ = false;
        break;
      }
      case SDL_KEYDOWN: {
        if (ev.key.keysym.sym == SDLK_ESCAPE) {
          std::cout << "SDLK_ESCAPE" << std::endl;
          is_running_ = false;
        } else if (ev.key.keysym.sym == SDLK_1) {
          options_.render_filled_triangle = !options_.render_filled_triangle;
        } else if (ev.key.keysym.sym == SDLK_2) {
          options_.render_wireframe = !options_.render_wireframe;
        } else if (ev.key.keysym.sym == SDLK_3) {
          options_.enable_back_face_culling = !options_.enable_back_face_culling;
        } else if (ev.key.keysym.sym == SDLK_4) {
          options_.render_vertex_points = !options_.render_vertex_points;
        }
        break;
      }
      default: {
        break;
      }
    }
  }

  void copy_color_buffer() const {
    SDL_UpdateTexture(context_.color_buffer_texture, nullptr, canvas_.get_color_buffer().data(), static_cast<int>(canvas_.get_width() * sizeof(std::uint32_t)));
    SDL_RenderCopy(context_.renderer, context_.color_buffer_texture, nullptr, nullptr);
  }

  void render() {
    namespace bm = bonfire::math;

    for (std::size_t entity_idx = 0; entity_idx < entities_.size(); entity_idx++) {
      auto& render_data = render_datas_[entity_idx];

      render_data.triangles.clear();

      const auto& vertices = entities_[entity_idx].drawable.vertices;
      const auto& indices = entities_[entity_idx].drawable.indices;
      const auto& transform = entities_[entity_idx].transform;

      for (std::size_t i = 0; i < indices.size();) {
        const auto& vertex0 = vertices[indices[i++]];
        const auto& vertex1 = vertices[indices[i++]];
        const auto& vertex2 = vertices[indices[i++]];

        // transform vertices
        const auto transformed_vertex0 = transform_vertex(vertex0, transform);
        const auto transformed_vertex1 = transform_vertex(vertex1, transform);
        const auto transformed_vertex2 = transform_vertex(vertex2, transform);

        // back face culling
        if (options_.enable_back_face_culling && should_render_triangle(transformed_vertex0, transformed_vertex1, transformed_vertex2)) {
          continue;
        }

        // project vertices
        const auto projected_vertex0 = project(transformed_vertex0);
        const auto projected_vertex1 = project(transformed_vertex1);
        const auto projected_vertex2 = project(transformed_vertex2);

        render_data.triangles.push_back(
          Triangle{
            .points = { projected_vertex0, projected_vertex1, projected_vertex2 },
            .avg_depth = (transformed_vertex0.z + transformed_vertex1.z + transformed_vertex2.z) / 3.0f
          }
        );
      }

      // sort the triangles by avg depth for painters algo, but a hacky way. Sometimes might not work
      std::ranges::sort(render_data.triangles, [](const Triangle& lhs, const Triangle& rhs) {
        return lhs.avg_depth < rhs.avg_depth;
      });
    }

    for (const auto& [triangles] : render_datas_) {

      for (const auto& tri : triangles) {
        if (options_.render_filled_triangle) {
          canvas_.draw_filled_triangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, 0xFF666666);
        }

        if (options_.render_wireframe) {
          // wireframe
          canvas_.draw_triangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, 0xFF666666);
        }

        if (options_.render_vertex_points) {
          canvas_.draw_rectangle(tri.points[0].x, tri.points[0].y, 3, 3, 0xFFFF0000);
          canvas_.draw_rectangle(tri.points[1].x, tri.points[1].y, 3, 3, 0xFFFF0000);
          canvas_.draw_rectangle(tri.points[2].x, tri.points[2].y, 3, 3, 0xFFFF0000);
        }
      }
    }


    copy_color_buffer();
    SDL_RenderPresent(context_.renderer);

    canvas_.clear_color(0xFF000000);
  }

  [[nodiscard]] static auto transform_vertex(const bonfire::math::Vec3& vertex, const TransformComponent& tr) noexcept -> bonfire::math::Vec3 {
    namespace bm = bonfire::math;

    // rotate
    auto processed_vertex = bm::rotate_x(vertex, tr.rotation.x);
    processed_vertex = bm::rotate_y(processed_vertex, tr.rotation.y);
    processed_vertex = bm::rotate_z(processed_vertex, tr.rotation.z);

    // translate
    processed_vertex += tr.position;

    return processed_vertex;
  }

  [[nodiscard]] auto should_render_triangle(const bonfire::math::Vec3& v0, const bonfire::math::Vec3& v1, const bonfire::math::Vec3& v2) const noexcept -> bool {
    namespace bm = bonfire::math;
    /*
     *  Find vectors v1 - v0 and v2 - v0
     *  Take their cross product and lets call it normal_vec
     *  Find the camera ray by substracting the camera position from v0
     *  Take the dot product between N and camera ray
     *  if dot product is less than 0, return false
     */

    const auto vec_ab = v1 - v0;
    const auto vec_ac = v2 - v0;

    const auto normal_vec = bm::cross_product(vec_ab, vec_ac);

    const auto camera_ray = v0 - camera_pos_;

    if (const auto dp = bm::dot_product(normal_vec, camera_ray); dp < 0.0f) {
      return false;
    }

    return true;
  }

  [[nodiscard]] auto project(const bonfire::math::Vec3& pos) const noexcept -> bonfire::math::Vec2 {
    constexpr static auto fov_factor = 640.0f;

    return bonfire::math::Vec2(
      ((fov_factor * pos.x) / pos.z) + static_cast<float>(canvas_.get_width()) / 2,
      ((fov_factor * pos.y) / pos.z) + static_cast<float>(canvas_.get_height()) / 2
    );
  }

  void update(float delta_time) {
    namespace bm = bonfire::math;

    for (auto& e : entities_) {
      e.update_transform(e.transform);
    }
  }

private:
  Canvas canvas_;
  Context context_;
  std::vector<Entity> entities_;
  std::vector<RenderData> render_datas_;
  bonfire::math::Vec3 camera_pos_;
  RenderOptions options_;
  bool is_running_;
};

}	// namespace swr
