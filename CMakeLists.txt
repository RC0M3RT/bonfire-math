cmake_minimum_required (VERSION 3.27)

set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  BonfireMath
  VERSION 0.0.1
  LANGUAGES CXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(
	-Weverything
	#-Wno-switch-enum
	#-Wno-signed-enum-bitfield
	#-Wno-deprecated-register
	-Wno-c++98-compat
	-Wno-c++98-compat-pedantic
	-Wno-c++98-c++11-compat-pedantic
	#-Wno-nested-anon-types
	#-Wno-gnu-anonymous-struct
	#-Wno-missing-prototypes
	#-Wno-documentation
	#-Wno-documentation-unknown-command
	#-Wno-weak-vtables
	#-Wno-unused-const-variable
	#-Wno-format-nonliteral
	#-Wno-global-constructors
	#-Wno-exit-time-destructors
	#-Wno-error=padded
	-Wno-float-equal # comparing floating point with == or != is unsafe [-Wfloat-equal]
    -fno-rtti
  )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  add_compile_options(
	  /Wall /GR-
  )
endif()

find_package(glfw3 CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

add_subdirectory(math)
add_subdirectory(app)
add_subdirectory(software_renderer)
add_subdirectory(test)

