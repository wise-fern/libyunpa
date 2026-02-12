import libyunpa;

#include <gtest/gtest.h>

TEST(Point2, Equality) {
  using namespace libyunpa;
  constexpr auto lhs = Point2{.x = 32, .y = 49};
  EXPECT_EQ(lhs, lhs);
}

TEST(Point2, Addition) {
  using namespace libyunpa;
  constexpr auto lhs = Point2{.x = 32, .y = 85};
  constexpr auto rhs = Point2{.x = 52, .y = 19};
  constexpr auto sum = Point2{.x = 84, .y = 104};
  EXPECT_EQ((lhs + rhs), sum);
}