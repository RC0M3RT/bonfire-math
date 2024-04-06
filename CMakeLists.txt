cmake_minimum_required (VERSION 3.27)

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  BonfireMath
  VERSION 0.0.1
  LANGUAGES CXX)

find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_subdirectory(math)
add_subdirectory(app)
add_subdirectory(software_renderer)
add_subdirectory(test)

