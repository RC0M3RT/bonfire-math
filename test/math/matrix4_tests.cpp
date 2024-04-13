#include <catch2/catch_test_macros.hpp>

#include <math/matrix4.hpp>

#include <iostream>

namespace bm = bonfire::math;

TEST_CASE( "Multiply MxN", "[Matrix4]" ) {

  const bm::Mat4 m{
    1.0f, 2.0f, 3.0f, 4.0f, // col1
    5.0f, 6.0f, 7.0f, 8.0f, // col2
    9.0f, 1.0f, 2.0f, 3.0f, // col3
    4.0f, 5.0f, 6.0f, 7.0f, // col4
  };

  const bm::Mat4 n{
    9.0f, 8.0f, 7.0f, 6.0f, // col1
    5.0f, 4.0f, 3.0f, 2.0f, // col2
    1.0f, 9.0f, 8.0f, 7.0f, // col3
    6.0f, 5.0f, 4.0f, 3.0f  // col4
  };

  const auto res = m * n;

  REQUIRE(res.column(0).x == 136.0f);
  REQUIRE(res.column(0).y == 103.0f);
  REQUIRE(res.column(0).z == 133.0f);
  REQUIRE(res.column(0).w == 163.0f);

  REQUIRE(res.column(1).x == 60.0f);
  REQUIRE(res.column(1).y == 47.0f);
  REQUIRE(res.column(1).z == 61.0f);
  REQUIRE(res.column(1).w == 75.0f);

  REQUIRE(res.column(2).x == 146.0f);
  REQUIRE(res.column(2).y == 99.0f);
  REQUIRE(res.column(2).z == 124.0f);
  REQUIRE(res.column(2).w == 149.0f);

  REQUIRE(res.column(3).x == 79.0f);
  REQUIRE(res.column(3).y == 61.0f);
  REQUIRE(res.column(3).z == 79.0f);
  REQUIRE(res.column(3).w == 97.0f);
}


TEST_CASE( "Multiply Mxv", "[Matrix4]" ) {
  const bm::Mat4 m{
    1.0f, 2.0f, 3.0f, 4.0f, // col1
    5.0f, 6.0f, 7.0f, 8.0f, // col2
    9.0f, 1.0f, 2.0f, 3.0f, // col3
    4.0f, 5.0f, 6.0f, 7.0f, // col4
  };

  const bm::Vec4 v{9.0f, 8.0f, 7.0f, 6.0f};

  const auto res = m * v;

  REQUIRE(res.x == 136.0f);
  REQUIRE(res.y == 103.0f);
  REQUIRE(res.z == 133.0f);
  REQUIRE(res.w == 163.0f);
}

