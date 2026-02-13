#include <gtest/gtest.h>
#include <random>

import libyunpa;

using namespace libyunpa;

class Point2Test
    : public testing::TestWithParam<std::tuple<int, int, int, int>> {
protected:
  Point2<int> lhs{};
  Point2<int> rhs{};

public:
  Point2Test() {
    auto [lhsx, lhsy, rhsx, rhsy] = GetParam();

    lhs = Point2{.x = lhsx, .y = lhsy};
    rhs = Point2{.x = rhsx, .y = rhsy};
  }
};

TEST_P(Point2Test, Equality) {
  EXPECT_EQ(lhs, lhs);
  EXPECT_EQ(rhs, rhs);
  EXPECT_NE(lhs, rhs);
}

TEST_P(Point2Test, Addition) {
  auto result = Point2{.x = lhs.x + rhs.x, .y = lhs.y + rhs.y};
  EXPECT_EQ(lhs + rhs, result);
}

TEST_P(Point2Test, Negation) {
  auto result = Point2{.x = -lhs.x, .y = -lhs.y};
  EXPECT_EQ(-lhs, result);
  result = Point2{.x = -rhs.x, .y = -rhs.y};
  EXPECT_EQ(-rhs, result);
}

TEST_P(Point2Test, Subtraction) {
  auto result = Point2{.x = lhs.x - rhs.x, .y = lhs.y - rhs.y};
  EXPECT_EQ(lhs - rhs, result);
}

namespace {
auto rng = std::mt19937(0);
}

INSTANTIATE_TEST_SUITE_P(Coordinates,
                         Point2Test,
                         testing::Values(std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{rng(), rng(), rng(), rng()},
                                         std::tuple{
                                             rng(), rng(), rng(), rng()}));
