#pragma once

#include <type_traits>
#include <format>
#include <string>
#include <string_view>

#include "matrix3.hpp"

namespace bonfire::math {

static std::string format(const Mat3& m, std::string name = "M") {
	std::string_view tmp = 
R"(
      | {0} {3} {6} |
  {9} = |	{1} {4} {7} |
      | {2} {5} {8} |
)";

  const auto& m00 = m.column(0).elem(0);  const auto& m10 = m.column(1).elem(0); const auto& m20 = m.column(2).elem(0);
  const auto& m01 = m.column(0).elem(1);  const auto& m11 = m.column(1).elem(1); const auto& m21 = m.column(2).elem(1);
  const auto& m02 = m.column(0).elem(2);  const auto& m12 = m.column(1).elem(2); const auto& m22 = m.column(2).elem(2);

  return std::vformat(tmp, std::make_format_args(m00, m01, m02, m10, m11, m12, m20, m21, m22, name));
}

static std::string format(const Vec3& v, std::string name = "v") {
	std::string_view tmp = 
R"(
      | {0} |
  {3} = |	{1} |
      | {2} |
)";

  return std::vformat(tmp, std::make_format_args(v.x, v.y, v.z, name));
}

}	// namespace bonfire::math



