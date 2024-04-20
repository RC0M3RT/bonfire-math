set(SoftwareRenderer_SOURCES
    "core/sdl.hpp"
    "core/context.hpp"
    "core/canvas.hpp"
    "core/entity.hpp"
    "core/components.hpp"
    "core/renderer.hpp"
    "core/pods.hpp"
    "core/utils.hpp"

    "main.cpp"
)

SET(CONTENT_BASE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/assets/")

configure_file("assets/swr_config.hpp.in" "${CMAKE_BINARY_DIR}/configured_files/include/internal_use_only/swr_config.hpp" ESCAPE_QUOTES)

add_executable(SoftwareRenderer ${SoftwareRenderer_SOURCES})

target_link_libraries(SoftwareRenderer PRIVATE
    SDL2::SDL2 BonfireMath tinyobjloader::tinyobjloader
)

target_include_directories(SoftwareRenderer PRIVATE ${CMAKE_BINARY_DIR}/configured_files/include/)
