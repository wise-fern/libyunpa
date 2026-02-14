#include <gtest/gtest.h>
#include <random>

import libyunpa;

class Point2 : public testing::TestWithParam<std::tuple<int, int, int, int>> {
protected:
  libyunpa::Point2<int> lhs{};
  libyunpa::Point2<int> rhs{};

public:
  Point2() {
    auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

    lhs = libyunpa::Point2{.x = lhsx, .y = lhsy};
    rhs = libyunpa::Point2{.x = rhsx, .y = rhsy};
  }
};

TEST_P(Point2, Equality) {
  EXPECT_TRUE(lhs == lhs);
  EXPECT_TRUE(rhs == rhs);
  EXPECT_FALSE(lhs == rhs);
}

TEST_P(Point2, Inequality) {
  EXPECT_TRUE(lhs != rhs);
  EXPECT_FALSE(lhs != lhs);
  EXPECT_FALSE(rhs != rhs);
}

TEST_P(Point2, Addition) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = lhsx + rhsx, .y = lhsy + rhsy};
  EXPECT_TRUE(lhs + rhs == result);
}

TEST_P(Point2, Negation) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = -lhsx, .y = -lhsy};
  EXPECT_TRUE(-lhs == result);
  result = libyunpa::Point2{.x = -rhsx, .y = -rhsy};
  EXPECT_TRUE(-rhs == result);
}

TEST_P(Point2, Subtraction) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = lhsx - rhsx, .y = lhsy - rhsy};
  EXPECT_EQ(lhs - rhs, result);
}

TEST_P(Point2, Multiplication) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = lhsx * rhsx, .y = lhsy * rhsy};
  EXPECT_EQ(lhs * rhs, result);
}

TEST_P(Point2, ScalarMultiplaction) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = lhsx * rhsx, .y = lhsy * rhsx};
  EXPECT_EQ(lhs * rhs.x, result);
}

TEST_P(Point2, Division) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = libyunpa::Point2{.x = lhsx / rhsx, .y = lhsy / rhsy};
  EXPECT_EQ(lhs / rhs, result);
}

namespace {
auto rng = std::mt19937(0);
}

INSTANTIATE_TEST_SUITE_P(System,
                         Point2,
                         testing::Values(std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{
                                             rng(), rng(), rng(), rng()}));
