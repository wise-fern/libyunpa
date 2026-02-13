#include <gtest/gtest.h>
#include <random>

import libyunpa;

using namespace libyunpa;

class Point2Tests
    : public testing::TestWithParam<std::tuple<int, int, int, int>> {
protected:
  Point2<int> lhs{};
  Point2<int> rhs{};

public:
  Point2Tests() {
    auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

    lhs = Point2{.x = lhsx, .y = lhsy};
    rhs = Point2{.x = rhsx, .y = rhsy};
  }
};

TEST_P(Point2Tests, Equality) {
  EXPECT_EQ(lhs, lhs);
  EXPECT_EQ(rhs, rhs);
  EXPECT_NE(lhs, rhs);
}

TEST_P(Point2Tests, Addition) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = lhsx + rhsx, .y = lhsy + rhsy};
  EXPECT_EQ(lhs + rhs, result);
}

TEST_P(Point2Tests, Negation) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = -lhsx, .y = -lhsy};
  EXPECT_EQ(-lhs, result);
  result = Point2{.x = -rhsx, .y = -rhsy};
  EXPECT_EQ(-rhs, result);
}

TEST_P(Point2Tests, Subtraction) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = lhsx - rhsx, .y = lhsy - rhsy};
  EXPECT_EQ(lhs - rhs, result);
}

TEST_P(Point2Tests, Multiplication) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = lhsx * rhsx, .y = lhsy * rhsy};
  EXPECT_EQ(lhs * rhs, result);
}

TEST_P(Point2Tests, ScalarMultiplaction) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = lhsx * rhsx, .y = lhsy * rhsx};
  EXPECT_EQ(lhs * rhs.x, result);
}

TEST_P(Point2Tests, Division) {
  auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

  auto result = Point2{.x = lhsx / rhsx, .y = lhsy / rhsy};
  EXPECT_EQ(lhs / rhs, result);
}

namespace {
auto rng = std::mt19937(0);
}

INSTANTIATE_TEST_SUITE_P(System,
                         Point2Tests,
                         testing::Values(std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{
                                             rng(), rng(), rng(), rng()}));
