#pragma once

#include "sdl.hpp"
#include <optional>

namespace swr {

struct Context {
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_Texture* color_buffer_texture = nullptr;

  [[nodiscard]] static auto create_context(int width, int height) -> std::optional<Context> {
    const auto res = SDL_Init(SDL_INIT_EVERYTHING);
    if (res != 0) {
      std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
      return std::nullopt;
    }

    Context ctx{};

    ctx.window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (ctx.window == nullptr) {
      std::cerr << "Could not create sdl window: " << SDL_GetError() << std::endl;
      return std::nullopt;
    }

    ctx.renderer = SDL_CreateRenderer(ctx.window, -1, 0);

    if (ctx.renderer == nullptr) {
      std::cerr << "Could not create sdl renderer: " << SDL_GetError() << std::endl;
      return std::nullopt;
    }

    ctx.color_buffer_texture = SDL_CreateTexture(
      ctx.renderer,
      SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING,
      width,
      height
    );

    if (ctx.color_buffer_texture == nullptr) {
      std::cerr << "Could not create sdl texture: " << SDL_GetError() << std::endl;
      return std::nullopt;
    }

    std::cout << "Context initialized..." << std::endl;

    return ctx;
  }

  void cleanup() {
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};

}	// namespace swr
