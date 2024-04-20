#pragma once
#include <type_traits>

namespace bonfire::math {

namespace coordinate_system {

// Coordinate system config
struct LeftHandedTag{};
struct RightHandedTag{};

} // namespace coordinate_system

template<typename T>
concept HandednessTag = requires
{
  std::is_same_v<T, coordinate_system::LeftHandedTag> || std::is_same_v<T, coordinate_system::RightHandedTag>;
};

namespace depth_range {

// Depth range config
struct ZeroToOneTag{};
struct NegativeOneToOneTag{};

} // namespace depth_range

template<typename T>
concept DepthRangeTag = requires
{
  std::is_same_v<T, depth_range::ZeroToOneTag> || std::is_same_v<T, depth_range::NegativeOneToOneTag>;
};

} // namespace bonfire::math

