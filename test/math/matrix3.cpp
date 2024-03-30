#include <catch2/catch_test_macros.hpp>

#include <math/matrix3.hpp>

namespace bm = bonfire::math;

TEST_CASE( "Zero initialize", "[Matrix3]" ) {
  bm::Mat3 m{};
  bm::Mat3 m2{};

  REQUIRE(0 == m[0][0]);
  REQUIRE(0 == m[0][1]);
  REQUIRE(0 == m[0][2]);

  REQUIRE(0 == m[1][0]);
  REQUIRE(0 == m[1][1]);
  REQUIRE(0 == m[1][2]);

  REQUIRE(0 == m[2][0]);
  REQUIRE(0 == m[2][1]);
  REQUIRE(0 == m[2][2]);

  REQUIRE(m == m2);
}

TEST_CASE( "Value initialize", "[Matrix3]" ) {
  bm::Mat3 m{42.0f};
  bm::Mat3 m2{42.0f};

  REQUIRE(42.0f == m[0][0]);
  REQUIRE(42.0f == m[0][1]);
  REQUIRE(42.0f == m[0][2]);

  REQUIRE(42.0f == m[1][0]);
  REQUIRE(42.0f == m[1][1]);
  REQUIRE(42.0f == m[1][2]);

  REQUIRE(42.0f == m[2][0]);
  REQUIRE(42.0f == m[2][1]);
  REQUIRE(42.0f == m[2][2]);

  REQUIRE(m == m2);
}

TEST_CASE( "Per member initialize", "[Matrix3]" ) {
  bm::Mat3 m{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  bm::Mat3 m2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

  REQUIRE(1.0f == m[0][0]);
  REQUIRE(2.0f == m[0][1]);
  REQUIRE(3.0f == m[0][2]);

  REQUIRE(4.0f == m[1][0]);
  REQUIRE(5.0f == m[1][1]);
  REQUIRE(6.0f == m[1][2]);

  REQUIRE(7.0f == m[2][0]);
  REQUIRE(8.0f == m[2][1]);
  REQUIRE(9.0f == m[2][2]);

  REQUIRE(m == m2);
}

TEST_CASE( "From Vectors", "[Matrix3]" ) {
  bm::Vec3 v1 {1.0f, 2.0f, 3.0f};
  bm::Vec3 v2 {4.0f, 5.0f, 6.0f};
  bm::Vec3 v3 {7.0f, 8.0f, 9.0f};

  bm::Mat3 m{v1, v2, v3};
  bm::Mat3 m2{v1, v2, v3};

  REQUIRE(1.0f == m[0][0]);
  REQUIRE(2.0f == m[0][1]);
  REQUIRE(3.0f == m[0][2]);

  REQUIRE(4.0f == m[1][0]);
  REQUIRE(5.0f == m[1][1]);
  REQUIRE(6.0f == m[1][2]);

  REQUIRE(7.0f == m[2][0]);
  REQUIRE(8.0f == m[2][1]);
  REQUIRE(9.0f == m[2][2]);

  REQUIRE(m == m2);
}

TEST_CASE( "Addition", "[Matrix3]" ) {
  bm::Mat3 m{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  bm::Mat3 m2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

  bm::Mat3 expected{2.0f, 4.0f, 6.0f, 8.0f, 10.0f, 12.0f, 14.0f, 16.0f, 18.0f};

  auto actual = m + m2;

  REQUIRE(expected == actual);
}

TEST_CASE( "Substraction", "[Matrix3]" ) {
  bm::Mat3 m{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  bm::Mat3 m2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

  bm::Mat3 expected{0};

  auto actual = m - m2;

  REQUIRE(expected == actual);
}
  
TEST_CASE( "Substraction2", "[Matrix3]" ) {
  bm::Mat3 m{14.0f, 2.0f, 3.0f, 65.0f, -1.0f, 6.0f, -42.0f, 8.0f, 9.0f};

  bm::Mat3 m2{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

  bm::Mat3 expected{13.0f, 0.0f, 0.0f, 61.0f, -6.0f, 0.0f, -49.0f, 0.0f, 0.0f};

  auto actual = m - m2;

  REQUIRE(expected == actual);
}
